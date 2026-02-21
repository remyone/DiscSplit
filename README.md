# 📁 DiscSplit - Split & Merge Files for Discord
- ⚡ **Splits large files into Discord-friendly chunks**
- 🔗 **Merges chunks back into original files**
- 🪓 **Bypasses Discord's 10MB file limit**
- 💻 **Written in C**

`Why in C?` - I wanted to practice file managament and test my hard skills in C!

### ⚒️Compiling
```bash
cd DiscSplit/
mkdir build
cd build
gcc -c ../FileAnalysis/fileAnalysis.c -o FA.o
gcc -c ../SplitFileContent/splitFileContent.c -o SFC.o -I ../FileAnalysis
gcc -c ../MergeFiles/mergeFiles.c -o MF.o -I ../SplitFileContent -I ../FileAnalysis
ar -rcs libfilelib FA.o MF.o SFC.o
cd ..
gcc main.c -L build/ -lfilelib -I FileAnalysis -I MergeFiles -I SplitFileContent -o DiscSplit
```

### 🔥Motivation

Obviously, my first reason to code this project is **to bypass the Discord's file limit** because I faced this issue myself. Plus, I've already said earlier that I wanted to test my "C" skills, especially with files. In addition, I want to learn CMake (it will be added later, that's goal №1!)

### 📋TODO-list
- **Implement CMake**

### License 
This project is open source and available under the [MIT License](https://github.com/remyone/DiscSplit/blob/main/LICENSE)
