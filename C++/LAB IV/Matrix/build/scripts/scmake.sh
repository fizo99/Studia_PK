cd ..
cmake -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -G "Unix Makefiles" -F CMAKE_CXX_FLAGS "-stdlib=lstdc++" ..