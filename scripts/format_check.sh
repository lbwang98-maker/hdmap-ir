#!/usr/bin/env bash
set -euo pipefail

# 自动收集仓库中的 C/C++ 文件并执行 clang-format 检查（不修改文件）
files=()
while IFS= read -r -d '' f; do
  files+=("$f")
done < <(find . \
  \( -path "./build" -o -path "./.git" -o -path "./_deps" -o -path "./.vscode" -o -path "./.idea" \) -prune -false \
  -o -type f \( -name "*.h" -o -name "*.hh" -o -name "*.hpp" -o -name "*.hxx" -o -name "*.c" -o -name "*.cc" -o -name "*.cpp" -o -name "*.cxx" \) -print0)

if [[ ${#files[@]} -eq 0 ]]; then
  echo "No C/C++ files found; skipping format check."
  exit 0
fi

clang-format --dry-run -Werror "${files[@]}"
