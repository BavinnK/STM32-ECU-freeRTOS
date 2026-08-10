# Check

## 今回のコミットを一言で

Docker ComposeでSTM32ファームウェアを再現ビルドできるようにし、元環境依存の絶対パスを相対化した変更。

## 使い方

リポジトリ直下で実行する。

```sh
docker compose run --rm firmware-build
```

この1コマンドで、Dockerコンテナの起動から `make` まで実行される。

コンテナ内では次を実行している。

```sh
make -C Debug clean && make -C Debug all -j
```

## 初回実行時

初回はDockerイメージをビルドするため、Ubuntuパッケージの取得が走る。

主な導入ツールは以下。

- `gcc-arm-none-eabi`
- `binutils-arm-none-eabi`
- `libnewlib-arm-none-eabi`
- `make`

## 生成物の場所

ビルド成果物はホスト側の `Debug` 配下に出る。

- `Debug/V2.4_ECU_STM32_PROJECT.elf`
- `Debug/V2.4_ECU_STM32_PROJECT.map`
- `Debug/V2.4_ECU_STM32_PROJECT.list`
- `Debug/default.size.stdout`
- `Debug/**/*.o`
- `Debug/**/*.d`
- `Debug/**/*.su`

## 検証済み内容

`docker compose run --rm firmware-build` でビルド完了を確認済み。

確認時のサイズ出力:

```text
text    data    bss     dec     hex     filename
31608   112     23344   55064   d718    V2.4_ECU_STM32_PROJECT.elf
```

## 注意点

- `Debug` 配下のMakefileはSTM32CubeIDEの生成物。
- CubeIDEで再生成すると、今回の相対パス化やDocker向けのフラグ調整が上書きされる可能性がある。
- Dockerビルド時は古いWindows由来の `.d` ファイルを読ませないため、先に `make clean` を実行している。
- 現状は `Debug` 配下の生成物がGit管理対象に含まれているため、ビルド後に `.o`、`.d`、`.su`、`.elf`、`.map`、`.list` などの差分が出る可能性がある。
- 共有プロジェクトとして安定させるなら、次は生成物を `.gitignore` し、手書きのトップレベル `Makefile` に寄せるのがよい。