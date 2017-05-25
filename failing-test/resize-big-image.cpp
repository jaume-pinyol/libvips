#include <iostream>
#include <pthread.h>
#include <vips/vips.h>
#include <vips/foreign.h>
//#include <vips/vips7compat.h>
#include <vips/intl.h>
#include <vips/vips8>
#include <vector>
#include <fstream>
#include <chrono>
#include <vips/vips8>

using namespace vips;
using namespace std;


static std::vector<char> ReadAllBytes(char const* filename)
{
    ifstream ifs(filename, ios::binary|ios::ate);
    ifstream::pos_type pos = ifs.tellg();

    std::vector<char>  result(pos);

    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);

    return result;
}

/*
Jaume  vipsRead type: 1
Jaume  vipsShrinkJpeg shrink: 2
Jaume  vipsAffine residualx: 0.555478 residualy: 0.555478 0
flattening bimg.vipsSaveOptions{Background:bimg.Color{R:0xff, G:0xff, B:0xff}, Quality:80, Compression:3, Type:1, Interlace:false, NoProfile:false, Interpretation:22}Saving bimg.ImageSize{Width:6000, Height:3999}Jaume  Pre Saving JPEG options &bimg.vipsSaveOptions{Background:bimg.Color{R:0xff, G:0xff, B:0xff}, Quality:80, Compression:3, Type:1, Interlace:false, NoProfile:false, Interpretation:22}
Jaume Saving JPEG tmpImage bimg.vipsSaveOptions{Background:bimg.Color{R:0xff, G:0xff, B:0xff}, Quality:80, Compression:3, Type:1, Interlace:false, NoProfile:false, Interpretation:22}
Jaume Saving JPEG tmpImage &{{{{0x28cbfa0} 2 [0 0 0 0] 0x2e78ec0} 1 0 0x2922920 0x2e7a6f0 0x2e7a710 0 0 0 [0 0 0 0] 0} 6000 3999 4 0 0 15 1 1 0 0 0 0 0 8 [0 0 0 0] <nil> <nil> 0x2e78fd0 <nil> 0 0 0 [0 0 0 0] 0x2e78e80 7 -1 <nil> 0 3064394248 [0 0 0 0] 0x7f813f877d5c 0x7f813f71c095 0x7f813f877d86 0x2925660 0x2e79030 0x2e78e30 <nil> 1 [0 0 0 0] 0x2e87460 0x7f8130001300 64 <nil> 0x29233c0 <nil> 0 [0 0 0 0] <nil> <nil> 0 1 0 <nil>} ptr <nil> length: 0 quality: 80 interlace: 0
*/
int main(int argc, char **argv) {

    string filename = argv[1];
    char* filename_t = &filename[0u];
//    float scale = 1/atoi(argv[2]);

    if(VIPS_INIT(argv[0]))
        return( -1 );

    double residualx = 0.555478;
    double residualy = 0.555478;
    int scale = 2;
    vips_cache_set_max(0);
    vips_cache_set_max_mem(0);
    VInterpolate interp = VInterpolate::new_from_name( "bilinear" );

    vector<char> bytes = ReadAllBytes(filename_t);
    char *buffer = new char[bytes.size()];
    copy(bytes.begin(), bytes.end(), buffer);

//    VipsBlob * blob = vips_blob_new( NULL, bytes, bytes.size());
    VImage out = VImage::new_from_buffer(buffer, bytes.size(), "", VImage::option()->
                                                                                     set("access", VIPS_ACCESS_RANDOM) ->
                                                                                     set("shrink", scale));
//    VImage out = VImage::jpegload_buffer(blob, VImage::option()->
//                   set("access", VIPS_ACCESS_RANDOM) ->
//                   set("shrink", scale));

    vector<double> abcd { residualx, 0, 0, residualy };
    out = out.affine(abcd, VImage::option()->
                    set("interpolate", interp));
//    vips_affine(in, out, a, b, c, d, "interpolate", interpolator, NULL)
//    vips_affine_interpolator(VipsImage *in, VipsImage **out, double a, double b, double c, double d, VipsInterpolate *interpolator) {
//    err := C.vips_affine_interpolator(input, &image, C.double(residualx), 0, 0, C.double(residualy), interpolator)
//    VipsBlob *object =
    out.jpegsave_buffer(VImage::option()->
                                                 set("strip", 1) ->
                                                 set("Q", 80) ->
                                                 set("optimize_coding", TRUE)->
                                                 set("interlace", TRUE));


//    out.write_to_file("test.jpg", VImage::option());

    vips_shutdown();
    return 0;
}
