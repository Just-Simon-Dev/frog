if ! command -v cmake 2>&1 >/dev/null
then
  echo "cmake not found"
  ${sudo apt install cmake}
fi

cmake  -DCMAKE_BUILD_TYPE=Debug -G Ninja -S ./ -B ./cmake-build-debug

./cmake-build-debug/frog
