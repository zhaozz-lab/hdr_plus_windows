compile in windows using visual studio 2022 or visual studio 2022 
# HDR+ Implementation
Original Document on the subject (by Timothy Brooks): http://timothybrooks.com/tech/hdr-plus

### Compilation instructions:
png halide libtiff libraw in thirdParty
```
mkdir build
cd build
cmake ..
using visual studio 2022 generate
```

### HDR+ algorithm examples:

There are three zip files with examples of the HDR+ algorithm at: http://www.gardling.com/hdr_plus

### Compiled Binary Usage:
```
Usage: ./hdrplus [-c comp -g gain (optional)] dir_path out_img raw_img1 raw_img2 [...]
```

The -c and -g flags change the amount of dynamic range compression and gain respectively. Although they are optional because they both have default values. 

### result
```
hdrplus.exe ./img burst33.png burst33_3.CR2 burst33_5.CR2 burst33_6.CR2
Opening ./img/burst33_3.CR2
Opening ./img/burst33_5.CR2
Opening ./img/burst33_6.CR2
Black point: 2047
White point: 15488
RGGB: 2.24609 1 1 1.39355
```
