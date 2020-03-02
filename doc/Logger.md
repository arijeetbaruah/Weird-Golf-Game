# Logger For Weird Golf Game

We 4 functions in the logger implementation:
1. info
2. error
3. debug
4. critical

Each of the function has 2 version:
`void info(T const& args);`
and
`void info(std::string fmt, T const... args);`

If you use the fmt format of the function. you can use `{}` to mark the args position. e.g `log.info("the number is: {}", 5);`

In order to use it. Include `Plugins/Logger/Logger.h` and create a logger object as `Logger log(string)`

