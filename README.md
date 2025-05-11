一些好玩的CPP特性代码

# Start
本项目依赖premake进行构造

前往[premake](https://premake.github.io/download)下载对应平台的可执行程序，并放到自己想要的位置

在项目的premake5.lua目录下执行以下命令（需要环境变量）

windows

```premake5 vs2022```

linux

```premake5 gmake```

macos

```premake5 xcode4```

可选参数参考https://premake.github.io/docs/Using-Premake

随后会生成对应平台的构建文件，按照对应的构建方式进行编译即可

# 当前进展
auto
decltype
