@echo off

fxc Resolve.hlsl /nologo /T vs_4_0 /O3 /Qstrip_reflect /Fh QuadVS.h /Vn Quad_VS /E QuadVS

fxc Resolve.hlsl /nologo /T ps_4_0 /O3 /Qstrip_reflect /Fh Resolve2PS.h /Vn Resolve2_PS /E ResolvePS /D NUM_SAMPLES=2
fxc Resolve.hlsl /nologo /T ps_4_0 /O3 /Qstrip_reflect /Fh Resolve4PS.h /Vn Resolve4_PS /E ResolvePS /D NUM_SAMPLES=4
fxc Resolve.hlsl /nologo /T ps_4_0 /O3 /Qstrip_reflect /Fh Resolve8PS.h /Vn Resolve8_PS /E ResolvePS /D NUM_SAMPLES=8
fxc Resolve.hlsl /nologo /T ps_4_0 /O3 /Qstrip_reflect /Fh Resolve16PS.h /Vn Resolve16_PS /E ResolvePS /D NUM_SAMPLES=16

fxc Resolve.hlsl /nologo /T ps_4_0 /O3 /Qstrip_reflect /Fh ClearPS.h /Vn Clear_PS /E ClearPS