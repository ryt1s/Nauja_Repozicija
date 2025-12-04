#!/usr/bin/env bash
set -e
echo "Running doxygen..."
if ! command -v doxygen >/dev/null 2>&1; then
  echo "Error: doxygen not found. Install doxygen (and graphviz for diagrams)." >&2
  exit 1
fi
doxygen Doxyfile
echo "Doxygen finished. Open docs/doxygen/html/index.html"
