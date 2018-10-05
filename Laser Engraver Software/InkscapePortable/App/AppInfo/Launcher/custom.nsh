${SegmentFile}

${SegmentInit}
	;An inelegant hack to include Ghostscript in the path, will be retired with PAL 3's Find Ghostscript
	ExpandEnvStrings $1 "%PAL:PortableAppsDir%"
	${If} ${FileExists} "$1\CommonFiles\Ghostscript\bin\*.*"
		WriteINIStr "$EXEDIR\App\AppInfo\Launcher\InkscapePortable.ini" "Environment" "PATH" "%PAL:PortableAppsDir%\CommonFiles\Ghostscript\bin;%PAL:PortableAppsDir%\CommonFiles\Ghostscript\lib;%PATH%"
	${Else}
		WriteINIStr "$EXEDIR\App\AppInfo\Launcher\InkscapePortable.ini" "Environment" "PATH" "%PATH%"
	${EndIf}
!macroend