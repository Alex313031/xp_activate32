gn gen out\Debug\&&ninja.bat -C out\Debug\ xp_activate32 -v -j 8&&copy /Y out\Debug\xp_activate32.exe Y:\xp_activate_debug.exe&&^
gn gen out\Release\&&ninja.bat -C out\Release\ xp_activate32 -v -j 8&&copy /Y out\Release\xp_activate32.exe Y:\xp_activate_rel.exe&&^
out\Debug\xp_activate32.exe
