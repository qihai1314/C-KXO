################################################
# Make file for CASIO fx-9860G SDK Addin
#
############################
# Directory defines
TCDIR = C:\Program Files\CASIO\fx-9860G SDK\OS\SH
OSDIR = C:\Program Files\CASIO\fx-9860G SDK\OS
APPDIR = C:\Users\Administrator\Desktop\2015-06-6交点法转线元推链表\2015-06-4交点法转线元推链表
OUTDIR = C:\Users\Administrator\Desktop\2015-06-6交点法转线元推链表\2015-06-4交点法转线元推链表\Debug

################
# Main Defines
SH_EXEDIR=$(TCDIR)\bin

# Hitachi SH C/C++ Compiler02 phase
SHCC02_EXE=shc.exe
SHCC02_DEP="$(OSDIR)\FX\include\fxlib.h" "cvs.h" "FileLine.h" "headfile.h" "MyFont.h" "Parameters_List.h" "runmain.h" "xy.h" "zbzfs.h"

# Hitachi SH Assembler03 phase
SHASM03_EXE=asmsh.exe

# Hitachi OptLinker04 phase
SHLINK04_EXE=Optlnk.exe
SHLINK04_DEP="$(OSDIR)\FX\lib\fx9860G_library.lib"
SHLINK04_DEP2="$(OSDIR)\FX\lib\setup.obj"

#######################
# Files to build
FILE0=Achievement_list
FILESRC0="$(APPDIR)\$(FILE0).c"
FILEOBJ0="$(OUTDIR)\$(FILE0).obj"
FILE1=ArcCalculation
FILESRC1="$(APPDIR)\$(FILE1).c"
FILEOBJ1="$(OUTDIR)\$(FILE1).obj"
FILE2=BMx
FILESRC2="$(APPDIR)\$(FILE2).c"
FILEOBJ2="$(OUTDIR)\$(FILE2).obj"
FILE3=celiang
FILESRC3="$(APPDIR)\$(FILE3).c"
FILEOBJ3="$(OUTDIR)\$(FILE3).obj"
FILE4=Chinese
FILESRC4="$(APPDIR)\$(FILE4).c"
FILEOBJ4="$(OUTDIR)\$(FILE4).obj"
FILE5=computeFS
FILESRC5="$(APPDIR)\$(FILE5).c"
FILEOBJ5="$(OUTDIR)\$(FILE5).obj"
FILE6=computeZS
FILESRC6="$(APPDIR)\$(FILE6).c"
FILEOBJ6="$(OUTDIR)\$(FILE6).obj"
FILE7=cvs
FILESRC7="$(APPDIR)\$(FILE7).c"
FILEOBJ7="$(OUTDIR)\$(FILE7).obj"
FILE8=data
FILESRC8="$(APPDIR)\$(FILE8).c"
FILEOBJ8="$(OUTDIR)\$(FILE8).obj"
FILE9=Distance_orientation
FILESRC9="$(APPDIR)\$(FILE9).c"
FILEOBJ9="$(OUTDIR)\$(FILE9).obj"
FILE10=DrawGraph
FILESRC10="$(APPDIR)\$(FILE10).c"
FILEOBJ10="$(OUTDIR)\$(FILE10).obj"
FILE11=File
FILESRC11="$(APPDIR)\$(FILE11).c"
FILEOBJ11="$(OUTDIR)\$(FILE11).obj"
FILE12=FileLine
FILESRC12="$(APPDIR)\$(FILE12).c"
FILEOBJ12="$(OUTDIR)\$(FILE12).obj"
FILE13=FSTOOL
FILESRC13="$(APPDIR)\$(FILE13).c"
FILEOBJ13="$(OUTDIR)\$(FILE13).obj"
FILE14=Graphics
FILESRC14="$(APPDIR)\$(FILE14).c"
FILEOBJ14="$(OUTDIR)\$(FILE14).obj"
FILE15=input
FILESRC15="$(APPDIR)\$(FILE15).c"
FILEOBJ15="$(OUTDIR)\$(FILE15).obj"
FILE16=Intersection_File
FILESRC16="$(APPDIR)\$(FILE16).c"
FILEOBJ16="$(OUTDIR)\$(FILE16).obj"
FILE17=Intersection_parameter
FILESRC17="$(APPDIR)\$(FILE17).c"
FILEOBJ17="$(OUTDIR)\$(FILE17).obj"
FILE18=JS
FILESRC18="$(APPDIR)\$(FILE18).c"
FILEOBJ18="$(OUTDIR)\$(FILE18).obj"
FILE19=Line element_File
FILESRC19="$(APPDIR)\$(FILE19).c"
FILEOBJ19="$(OUTDIR)\$(FILE19).obj"
FILE20=Line element_parameter
FILESRC20="$(APPDIR)\$(FILE20).c"
FILEOBJ20="$(OUTDIR)\$(FILE20).obj"
FILE21=Linear_calculation
FILESRC21="$(APPDIR)\$(FILE21).c"
FILEOBJ21="$(OUTDIR)\$(FILE21).obj"
FILE22=MyFont
FILESRC22="$(APPDIR)\$(FILE22).c"
FILEOBJ22="$(OUTDIR)\$(FILE22).obj"
FILE23=MyMenu
FILESRC23="$(APPDIR)\$(FILE23).c"
FILEOBJ23="$(OUTDIR)\$(FILE23).obj"
FILE24=OutPut
FILESRC24="$(APPDIR)\$(FILE24).c"
FILEOBJ24="$(OUTDIR)\$(FILE24).obj"
FILE25=Parameters_List
FILESRC25="$(APPDIR)\$(FILE25).c"
FILEOBJ25="$(OUTDIR)\$(FILE25).obj"
FILE26=Plane_File
FILESRC26="$(APPDIR)\$(FILE26).c"
FILEOBJ26="$(OUTDIR)\$(FILE26).obj"
FILE27=Plane_parameter
FILESRC27="$(APPDIR)\$(FILE27).c"
FILEOBJ27="$(OUTDIR)\$(FILE27).obj"
FILE28=Project_setup
FILESRC28="$(APPDIR)\$(FILE28).c"
FILEOBJ28="$(OUTDIR)\$(FILE28).obj"
FILE29=register
FILESRC29="$(APPDIR)\$(FILE29).c"
FILEOBJ29="$(OUTDIR)\$(FILE29).obj"
FILE30=SDDM
FILESRC30="$(APPDIR)\$(FILE30).c"
FILEOBJ30="$(OUTDIR)\$(FILE30).obj"
FILE31=Set
FILESRC31="$(APPDIR)\$(FILE31).c"
FILEOBJ31="$(OUTDIR)\$(FILE31).obj"
FILE32=Vertical section_File
FILESRC32="$(APPDIR)\$(FILE32).c"
FILEOBJ32="$(OUTDIR)\$(FILE32).obj"
FILE33=Vertical section_parameter
FILESRC33="$(APPDIR)\$(FILE33).c"
FILEOBJ33="$(OUTDIR)\$(FILE33).obj"
FILE34=xy
FILESRC34="$(APPDIR)\$(FILE34).c"
FILEOBJ34="$(OUTDIR)\$(FILE34).obj"
FILE35=zbzfs
FILESRC35="$(APPDIR)\$(FILE35).c"
FILEOBJ35="$(OUTDIR)\$(FILE35).obj"
FILE36=zfset
FILESRC36="$(APPDIR)\$(FILE36).c"
FILEOBJ36="$(OUTDIR)\$(FILE36).obj"
FILE37=ZSTOOL
FILESRC37="$(APPDIR)\$(FILE37).c"
FILEOBJ37="$(OUTDIR)\$(FILE37).obj"
RFILE=FXADDINror
USERALLOBJ=$(FILEOBJ0) $(FILEOBJ1) $(FILEOBJ2) $(FILEOBJ3) $(FILEOBJ4) $(FILEOBJ5) $(FILEOBJ6) $(FILEOBJ7) $(FILEOBJ8) $(FILEOBJ9) \
      $(FILEOBJ10) $(FILEOBJ11) $(FILEOBJ12) $(FILEOBJ13) $(FILEOBJ14) $(FILEOBJ15) $(FILEOBJ16) $(FILEOBJ17) $(FILEOBJ18) $(FILEOBJ19) \
      $(FILEOBJ20) $(FILEOBJ21) $(FILEOBJ22) $(FILEOBJ23) $(FILEOBJ24) $(FILEOBJ25) $(FILEOBJ26) $(FILEOBJ27) $(FILEOBJ28) $(FILEOBJ29) \
      $(FILEOBJ30) $(FILEOBJ31) $(FILEOBJ32) $(FILEOBJ33) $(FILEOBJ34) $(FILEOBJ35) $(FILEOBJ36) $(FILEOBJ37)

#######################
# nmake "all" statement

ALL:  SH_ENV \
	$(USERALLOBJ) \
	$(OUTDIR)\$(RFILE).bin \

####################
# Description blocks

!MESSAGE %3#C$z`&'0?
!MESSAGE
!MESSAGE Executing Hitachi SH C/C++ Compiler/Assembler phase
!MESSAGE

SH_ENV : 
	set SHC_INC=$(TCDIR)\include
	set PATH=$(TCDIR)\bin
	set SHC_LIB=$(TCDIR)\bin
	set SHC_TMP=$(OUTDIR)

$(FILEOBJ0) : $(FILESRC0) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ0)
-show=source
-listfile="$(OUTDIR)\$(FILE0).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC0)
-lang=c
-nologo
-debug
<<

$(FILEOBJ1) : $(FILESRC1) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ1)
-show=source
-listfile="$(OUTDIR)\$(FILE1).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC1)
-lang=c
-nologo
-debug
<<

$(FILEOBJ2) : $(FILESRC2) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ2)
-show=source
-listfile="$(OUTDIR)\$(FILE2).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC2)
-lang=c
-nologo
-debug
<<

$(FILEOBJ3) : $(FILESRC3) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ3)
-show=source
-listfile="$(OUTDIR)\$(FILE3).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC3)
-lang=c
-nologo
-debug
<<

$(FILEOBJ4) : $(FILESRC4) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ4)
-show=source
-listfile="$(OUTDIR)\$(FILE4).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC4)
-lang=c
-nologo
-debug
<<

$(FILEOBJ5) : $(FILESRC5) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ5)
-show=source
-listfile="$(OUTDIR)\$(FILE5).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC5)
-lang=c
-nologo
-debug
<<

$(FILEOBJ6) : $(FILESRC6) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ6)
-show=source
-listfile="$(OUTDIR)\$(FILE6).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC6)
-lang=c
-nologo
-debug
<<

$(FILEOBJ7) : $(FILESRC7) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ7)
-show=source
-listfile="$(OUTDIR)\$(FILE7).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC7)
-lang=c
-nologo
-debug
<<

$(FILEOBJ8) : $(FILESRC8) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ8)
-show=source
-listfile="$(OUTDIR)\$(FILE8).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC8)
-lang=c
-nologo
-debug
<<

$(FILEOBJ9) : $(FILESRC9) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ9)
-show=source
-listfile="$(OUTDIR)\$(FILE9).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC9)
-lang=c
-nologo
-debug
<<

$(FILEOBJ10) : $(FILESRC10) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ10)
-show=source
-listfile="$(OUTDIR)\$(FILE10).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC10)
-lang=c
-nologo
-debug
<<

$(FILEOBJ11) : $(FILESRC11) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ11)
-show=source
-listfile="$(OUTDIR)\$(FILE11).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC11)
-lang=c
-nologo
-debug
<<

$(FILEOBJ12) : $(FILESRC12) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ12)
-show=source
-listfile="$(OUTDIR)\$(FILE12).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC12)
-lang=c
-nologo
-debug
<<

$(FILEOBJ13) : $(FILESRC13) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ13)
-show=source
-listfile="$(OUTDIR)\$(FILE13).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC13)
-lang=c
-nologo
-debug
<<

$(FILEOBJ14) : $(FILESRC14) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ14)
-show=source
-listfile="$(OUTDIR)\$(FILE14).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC14)
-lang=c
-nologo
-debug
<<

$(FILEOBJ15) : $(FILESRC15) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ15)
-show=source
-listfile="$(OUTDIR)\$(FILE15).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC15)
-lang=c
-nologo
-debug
<<

$(FILEOBJ16) : $(FILESRC16) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ16)
-show=source
-listfile="$(OUTDIR)\$(FILE16).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC16)
-lang=c
-nologo
-debug
<<

$(FILEOBJ17) : $(FILESRC17) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ17)
-show=source
-listfile="$(OUTDIR)\$(FILE17).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC17)
-lang=c
-nologo
-debug
<<

$(FILEOBJ18) : $(FILESRC18) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ18)
-show=source
-listfile="$(OUTDIR)\$(FILE18).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC18)
-lang=c
-nologo
-debug
<<

$(FILEOBJ19) : $(FILESRC19) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ19)
-show=source
-listfile="$(OUTDIR)\$(FILE19).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC19)
-lang=c
-nologo
-debug
<<

$(FILEOBJ20) : $(FILESRC20) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ20)
-show=source
-listfile="$(OUTDIR)\$(FILE20).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC20)
-lang=c
-nologo
-debug
<<

$(FILEOBJ21) : $(FILESRC21) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ21)
-show=source
-listfile="$(OUTDIR)\$(FILE21).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC21)
-lang=c
-nologo
-debug
<<

$(FILEOBJ22) : $(FILESRC22) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ22)
-show=source
-listfile="$(OUTDIR)\$(FILE22).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC22)
-lang=c
-nologo
-debug
<<

$(FILEOBJ23) : $(FILESRC23) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ23)
-show=source
-listfile="$(OUTDIR)\$(FILE23).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC23)
-lang=c
-nologo
-debug
<<

$(FILEOBJ24) : $(FILESRC24) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ24)
-show=source
-listfile="$(OUTDIR)\$(FILE24).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC24)
-lang=c
-nologo
-debug
<<

$(FILEOBJ25) : $(FILESRC25) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ25)
-show=source
-listfile="$(OUTDIR)\$(FILE25).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC25)
-lang=c
-nologo
-debug
<<

$(FILEOBJ26) : $(FILESRC26) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ26)
-show=source
-listfile="$(OUTDIR)\$(FILE26).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC26)
-lang=c
-nologo
-debug
<<

$(FILEOBJ27) : $(FILESRC27) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ27)
-show=source
-listfile="$(OUTDIR)\$(FILE27).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC27)
-lang=c
-nologo
-debug
<<

$(FILEOBJ28) : $(FILESRC28) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ28)
-show=source
-listfile="$(OUTDIR)\$(FILE28).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC28)
-lang=c
-nologo
-debug
<<

$(FILEOBJ29) : $(FILESRC29) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ29)
-show=source
-listfile="$(OUTDIR)\$(FILE29).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC29)
-lang=c
-nologo
-debug
<<

$(FILEOBJ30) : $(FILESRC30) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ30)
-show=source
-listfile="$(OUTDIR)\$(FILE30).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC30)
-lang=c
-nologo
-debug
<<

$(FILEOBJ31) : $(FILESRC31) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ31)
-show=source
-listfile="$(OUTDIR)\$(FILE31).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC31)
-lang=c
-nologo
-debug
<<

$(FILEOBJ32) : $(FILESRC32) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ32)
-show=source
-listfile="$(OUTDIR)\$(FILE32).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC32)
-lang=c
-nologo
-debug
<<

$(FILEOBJ33) : $(FILESRC33) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ33)
-show=source
-listfile="$(OUTDIR)\$(FILE33).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC33)
-lang=c
-nologo
-debug
<<

$(FILEOBJ34) : $(FILESRC34) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ34)
-show=source
-listfile="$(OUTDIR)\$(FILE34).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC34)
-lang=c
-nologo
-debug
<<

$(FILEOBJ35) : $(FILESRC35) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ35)
-show=source
-listfile="$(OUTDIR)\$(FILE35).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC35)
-lang=c
-nologo
-debug
<<

$(FILEOBJ36) : $(FILESRC36) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ36)
-show=source
-listfile="$(OUTDIR)\$(FILE36).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC36)
-lang=c
-nologo
-debug
<<

$(FILEOBJ37) : $(FILESRC37) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ37)
-show=source
-listfile="$(OUTDIR)\$(FILE37).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC37)
-lang=c
-nologo
-debug
<<

!MESSAGE
!MESSAGE Executing Hitachi OptLinker04 phase
!MESSAGE

"$(OUTDIR)\$(RFILE).bin" : $(USERALLOBJ) $(SHLINK04_DEP2) $(SHLINK04_DEP)
	"$(SH_EXEDIR)\$(SHLINK04_EXE)" -subcommand=<<
noprelink
sdebug
rom D=R
nomessage 
list "$(OUTDIR)\$(RFILE).map"
show symbol
nooptimize
start P_TOP,P,C,D,C$VTBL,C$INIT/0300200,B_BR_Size,B,R/08100000
fsymbol P
nologo
input $(USERALLOBJ)
input $(SHLINK04_DEP2)
library $(SHLINK04_DEP)
output "$(OUTDIR)\$(RFILE).abs"
-nomessage=1100
end
input "$(OUTDIR)\$(RFILE).abs"
form binary
output "$(OUTDIR)\$(RFILE).bin"
exit
<<

