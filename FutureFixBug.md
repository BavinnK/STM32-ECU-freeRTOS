# Future Fix Bugs

このメモは、初回解析とDocker化作業で見つかった修正候補を残すためのものです。

## 優先度高

### 1. `xECUDataQueue` に送っているデータ型が間違っている可能性

- 場所: `Core/Src/main.c`
- `xECUDataQueue` は `ECUData_T1` を格納するキューとして作成されている。
- しかし `xTaskECULogic()` では `fuel_lvl` のみを送信している。

```c
xECUDataQueue = xQueueCreate(1, sizeof(ECUData_T1));
...
xQueueOverwrite(xECUDataQueue, &fuel_lvl);
```

- `xTaskTFTdraw()` 側では `ECUData_T1` として受信しているため、構造体の中身が壊れた状態で扱われる可能性が高い。
- 修正案: `fuel_lvl` ではなく `current_state_disp` を送信する。

```c
xQueueOverwrite(xECUDataQueue, &current_state_disp);
```

### 2. TFT表示に使っている値が入れ替わっている可能性

- 場所: `Core/Src/main.c`
- `xTaskTFTdraw()` 内で、表示ラベルと実際に使っているフィールドが一致していない。

```c
sprintf(buff, "Oil Temp: %dC", recived_data.fan_cmd);
sprintf(buff, "Fuel Percent: %d", recived_data.temperature_c);
sprintf(buff, "Fan State: %d", recived_data.fuel_percent);
```

- 想定される対応:

```c
sprintf(buff, "Oil Temp: %dC", recived_data.temperature_c);
sprintf(buff, "Fuel Percent: %d", recived_data.fuel_percent);
sprintf(buff, "Fan State: %d", recived_data.fan_cmd);
```

## 優先度中

### 3. READMEの「HAL Purge」と実コードの状態に差がある

- READMEではHAL依存を排除した設計と説明されている。
- 実コードでは `HAL_Init()`、`stm32f4xx_hal.h`、HALドライバ群、`USE_HAL_DRIVER` が残っている。
- 完全ベアメタル化するのか、Cube/HAL併用プロジェクトとして整理するのか方針を決めた方がよい。

### 4. CubeMX設定と実際のクロック設定に差がある

- `.ioc` ではSYSCLK 90MHz相当の設定が残っている。
- 実コードでは `systemClock_180MHz()` により180MHzへ設定している。
- CubeMX再生成時にクロック設定や生成コードが食い違う可能性がある。

### 5. `Debug` 配下の生成物がGit管理されている

- `Debug/**/*.o`、`Debug/**/*.d`、`Debug/**/*.su`、`Debug/*.elf`、`Debug/*.map`、`Debug/*.list` などが管理対象に含まれている。
- DockerビルドやCubeIDEビルドのたびに差分が大量に出る可能性がある。
- 共有プロジェクトとしては、生成物を `.gitignore` に移して、ソースとビルド定義だけを管理する方がよい。

### 6. `Debug` 配下のMakefileがCubeIDE再生成で上書きされる可能性

- 今回、Dockerビルド用に以下を修正済み。
  - 元環境の絶対パスを `../...` に相対化。
  - Ubuntu標準の `arm-none-eabi-gcc` で未対応の `-fcyclomatic-complexity` を削除。
- ただし `Debug/*.mk` はSTM32CubeIDE生成物なので、CubeIDEで再生成すると元に戻る可能性がある。
- 根本対応案: トップレベルに手書きの `Makefile` を作り、Dockerはそれを使う。

### 7. Docker内ツールチェーンとCubeIDE同梱ツールチェーンのバージョン差

- 元の生成Makefileには `GNU Tools for STM32 (13.3.rel1)` と記載がある。
- DockerではUbuntuパッケージの `gcc-arm-none-eabi` を使用している。
- ビルドは通るが、厳密な再現性を高めるならツールチェーンバージョンを固定する方がよい。

## 優先度低 / 確認事項

### 8. HC-SR04のタイマコメントと設定値のズレ

- `TIM1->PSC = 179` は180MHz前提なら1MHz tickになる。
- コメントには一部 `84 MHz / (83+1)` と古い前提らしき記述が残っている。
- 実動作には大きな問題がない可能性もあるが、コメントは修正した方が混乱が少ない。

### 9. USARTのボーレート計算コメントと実クロックの整合性

- `set_baud()` のコメントではAPB1が42MHzと書かれている。
- 180MHz設定ではAPB1は45MHz想定。
- BRR固定値が現在のクロックに対して正しいか確認が必要。

## 対応済み

### `Debug` 配下の元環境絶対パス

- `C:/Users/pc/Desktop/STM_PROJECTS/...` と `C:\Users\pc\Desktop\STM_PROJECTS\...` は `Debug` 配下のMakefileから除去済み。
- 現在は `../Core/...` や `../STM32F446RETX_FLASH.ld` を使う形に変更済み。