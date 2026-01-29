#!/usr/bin/env bash
set -euo pipefail

# 枚举仓库下所有 C/C++ 文件（排除 build/.git 等常见目录），进行就地格式化
files=$(find . \
  \( -path './build' -o -path './.git' -o -path './_deps' -o -path './.vscode' -o -path './.idea' \) -prune -false \
  -o -type f \( -name '*.h' -o -name '*.hh' -o -name '*.hpp' -o -name '*.hxx' -o -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.cxx' \))

if [[ -z "$files" ]]; then
  echo "No C/C++ files found; nothing to format."
  exit 0
fi

echo "$files" | tr '\n' '\0' | xargs -0 clang-format -i
