
# Figa OS

Figa Systems FOSKRNL                                
FOSKRNL is advanced monolithic kernel system
 


## About us

Started from nothing continue with my friend

![ver](https://img.shields.io/badge/version-debug-debug?style=flat-square&logo=whitesource
)

![ver](https://img.shields.io/badge/Intel-Support-Support?style=flat-square&logo=intel&logoColor=black&labelColor=blue
)

![ver](https://img.shields.io/badge/Compile-unsuccessful-unsuccessful?style=flat-square&logoColor=white&labelColor=yellow&color=red
)


## Some links about us

 - [placeholder](placeholder)

## Documentation

[Documentation](https://linktodocumentation)


## Compiling

To Compile Debug build you need: GCC, nasm

```bash
  gcc -o FOSKRNL.bin /src/drivers/vga.c
```


## Changelog
BUILD.DBG.PUBLIC.0.ricerose
>Added Driver-Device managment system
>Rewrited VGA Driver
## Usage of API
To add new driver use 
```bash
  register_driver(*nameofdriver*)
```
then it return you id of driver


to remove driver use 
```bash
  unregister_driver(*nameofdriver*)
```
to init vga (reset vga driver) use
```bash
  init_vga(*backgroundclr* *forgegroundcolor*)
```

to print use 
```bash
  print_string("*string*",*/n*)
```

## Code errors
>0X3D4 VGA FAULT   
>FxFFF INIT FAULT   
>0x495 MEMORY ERROR   
>0x101 IO ERROR   
>0x16F SUBSYSTEM DISABLED   
>0x435 INVALID HANDLE     
         
