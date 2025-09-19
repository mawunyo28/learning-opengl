cmake -B build

# Compile commands
ln -s build/compile_commands.json .

cmake --build build

cd build && ./learngl
