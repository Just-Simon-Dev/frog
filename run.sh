if ! command -v cmake 2>&1 >/dev/null
then
  echo "cmake not found"
  ${sudo apt install cmake}
fi

cmake -S . -B build
cmake --build build

cmake --build build --target run

make run