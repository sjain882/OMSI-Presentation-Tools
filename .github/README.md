# OMSI Presentation Tools

<div align="center">

![SCREENSHOT](https://github.com/sjain882/OMSI-Presentation-Tools/blob/main/.github/Preview.png?raw=true)

[![ISSUES](https://img.shields.io/github/issues/sjain882/OMSI-Presentation-Tools?color=FF6D00&style=flat)](https://github.com/sjain882/OMSI-Presentation-Tools/issues)
[![VERSION](https://img.shields.io/github/v/release/sjain882/OMSI-Presentation-Tools?color=FF6D00&style=flat&label=version)](https://github.com/sjain882/OMSI-Presentation-Tools/releases/latest)
[![YOUTUBE TUTORIAL](https://img.shields.io/badge/-YouTube%20Tutorial-%23BF360C)](https://www.youtube.com/watch?v=YrbM-jaZYls)
[![STEAM GUIDE](https://img.shields.io/badge/-Steam%20Guide-%2301579B?style=flat)](https://steamcommunity.com/sharedfiles/filedetails/?id=2722795667)
[![DOWNLOAD](https://img.shields.io/github/downloads/sjain882/OMSI-Presentation-Tools/total?color=2E7D32&label=Download&style=flat)](https://github.com/sjain882/OMSI-Presentation-Tools/releases/latest)

Assorted tools to aid the creation of high-quality screenshots & videos for [OMSI 2](https://store.steampowered.com/app/252530).

Currently in very early stages.
</div>

‎
## Features:

- Compatibility with OMSI 2 v2.2.032 ("Tram compatible" patch) and v2.3.004 (latest version)
- Override the FoV (Field-of-View) of the Free Map (F4) Camera to a custom value (1.0-150.0°)
- Works when multiple instances of OMSI 2 are running (don't ask why, it **[just works™](https://github.com/sjain882/OMSI-Presentation-Tools/raw/main/.github/Multi-instance.png?raw=true)**)
- Can be injected into Omsi.exe (in the main menu - saves relaunching OMSI if you forgot to install - can take up to 10 mins on larger installs)

‎
## Planned features (hopefully):

- Adjust the Z height of the bus's pseudo shadow (`[isshadow]` mesh in the model configuration file)
- Define pre-defined camera movement sequences / keyframes (**[HLAE](https://github.com/advancedfx/advancedfx)**-like)
- Free-roam/look camera mode (via F4 camera manipulation) with seamless toggling
- Override bus presentation variables such as dirt, wetness, functional maintainence levels, per-wheel suspension, etc
- Override the `Snd_OutsideVol` variable for the current vehicle (controls volume of surroundings)
- Override the FOV, angles, positioning & (probably not) roll of all cameras
- Pedestrian mode with view bobbing, footstep sounds that consider texture material configurations (manipulate unfinished F11 camera?)
- Save modified camera attributes to `*.bus` & `*.ovh` files
- Spawn several morphable & movable chromakeys & toggle between red, blue & green colours
- Speedhack (slow/fast) the game - Cheat Engine's speedhack does not work properly with OMSI 2
- Temporarily override the time of day & weather attributes without affecting schedules
- Toggle application of `[viewpoint]` model configuration file tags, to allow meshes to draw in any camera mode (F1/F2/F3/F4)

###### Not confirmed / for the distant future (possibly never)
- TrackIR integration for any free roam camera, if achieved
- Inject toggleable native-like SSAO, DoF and misc filters into the rendering pipeline with customisable parameters with DirectX hooking or **[wrapping](https://github.com/elishacloud/dxwrapper)**
- Take screenshots at several times the currently set screen resolution (**[rendering to texture](https://gamedev.net/forums/topic/620712-c-directx9-render-to-texture/4915418/)**)

‎
## Important!

###### Anti-cheat warning

- Due to the nature of this tool, it is possible some game anti-cheats will flag this software. 

- Thus, **please ensure you keep all games which have anti-cheats closed while running OMSI 2 with OMSI Presentation Tools.** 

###### More information

- In theory there should be no issues since this tool restricts itself to memory regions OMSI has read-access to, but its possible it could be flagged up. The same applies to antivirus detections.

- As well as this, the OmniNavigation and Bus Company Simulator Addon DLCs read directly from to OMSI 2's process memory, similar to this tool. These DLCs have been public for several years and nobody has reported issues yet.

- Although all of these cases are extremely unlikely, if not impossible, please note that **I cannot be held personally responsible (directly or indirectly)** if usage of this tool results in an anti-cheat ban in other games, the breaking of your OMSI install or other software, or loss of data.

- Users will be reminded of this via a pop-up message box upon first launch of the tool (only).

‎
## Installation & usage:

Please refer to the **[full in-depth Steam guide](https://steamcommunity.com/sharedfiles/filedetails/?id=2722795667)**.

**[YouTube tutorial & suggested usage](https://www.youtube.com/watch?v=YrbM-jaZYls)**

- This tool requires the **[Visual C++ Redistributable Runtimes](https://www.techpowerup.com/download/visual-c-redistributable-runtime-package-all-in-one/)**.

- Also required is uninterrupted access to OMSI 2's log file (`OMSI 2\logfile.txt`). If this is not accessible for any reason (open handle, or `-nolog` OMSI 2 launch option) the tool will exit on launch.

- You are not required to run OMSI 2 as administrator for this tool to work.

Using OMSI Presentation Tools for a YouTube video you're creating? Why not leave a link to this tool in the description so others can enjoy it too?

‎
## Known issues:

- Entire UI has hardcoded coordinates and doesn't DPI scale properly (although perfectly usable). For me, C++/CLI is hell to work with and some methods just aren't recognised in the assembly... will eventually move to Dear ImGui 1.86+ / Docking (or failing that - C++ that calls C# WPF or C# Windows Forms for UI).
- Some features like automatically disabling the UI when a map is unloaded, updating label text with status aren't possible right now as I can't get the static dllmain code to interact with the non-static Windows Form in any way. See above point.
- Closing the tool doesn't fully detach it from OMSI, it just gets rid of the UI and stops the main program loop. Not a major issue, but not graceful or proper. Can fix this when I learn more about multithreading.

‎
## FAQ:

**Q:** Why didn't you put the GUI in an overlay for OMSI 2 instead of having an extra window floating around?

**A:** OMSI 2 is already a pretty unstable game. A host of compatibility issues with game overlays (NVIDIA Share, Discord, Steam) need to be considered when adding your own overlay. As well as this, users may be using either the stock DX9 game, DX12PY (DX12) or DXVK (Vulkan), and may be using SweetFX, ENB or ReShade combined with either of those. This is simply too many combinations to consider and is not a valuable use of my time. No need to add potential instability or unnecessary resource usage for such a simple tool right now.

For user level FAQs, please refer to the "Frequently Asked Questions" section of the **[Steam guide](https://steamcommunity.com/sharedfiles/filedetails/?id=2722795667)**.

‎
## Digital Signing of Release Binaries:

All `*.dll` binary files of this project compiled by me are digitally self-signed. The attached certificate should carry this serial number:

`18f6cc78c0fa778b4545c6d9d135cb52`

If the serial number on your copy does not match this, or the digital certificate is missing the file has potentially been tampered with and should be deleted immediately.

You can check this by right clicking on the `OMSIPresentationTools` .dll / Application extension file > Properties > Digital Signatures > Select the one named "sjain882" > Details > View Certificate > Details > Serial Number.

‎
## Building:

There is no specific build process. Simply install Visual Studio Community (I used 2019) with C++ Desktop and [CLR Workloads](https://www.youtube.com/watch?v=HcxlYkU8aY0) support, clone this repo, open the solution (`*.sln`) file, set the Configuration to Release x86 and run Build > Build solution.

You might need to remove my post-build event from Solution Properties > Build Events > Post-Build event (Visual Studio 2019).

Lower versions of Visual Studio should work, but I used VS 2019 with the C++17 language standard.

‎
## License:

This software is licensed under the GNU General Public License v3 (GPL-3) licence. Please see https://www.gnu.org/licenses/gpl-3.0.en.html for more information.

‎
## Credits:

- **[sjain882](https://github.com/sjain882)** - Creator of this tool

- **[rev_eng_e](https://github.com/rev-eng-e)** - Creator of array of Byte (AoB) pattern scanner

- **[win32kbase / Wolfie](https://github.com/win32kbase)** and **[ficool2](https://github.com/ficool2)** - assistance with reverse engineering & code

- **[Anonim17PL](https://github.com/Anonim17PL)** - author of several free and open-source OMSI plugins which were helpful for this project

- **[value1](https://forum.omnibussimulator.de/index.php?user/18150-value1/)** - Original [barebones C++ plugin base](https://forum.omnibussimulator.de/forum/index.php?thread/11008-programming-of-the-plugin-interface/&postID=286009#post286009) to extract variable values out of OMSI ([archive](https://web.archive.org/web/20200526071900/https://forum.omnibussimulator.de/forum/index.php?thread/11008-programming-of-the-plugin-interface/&postID=286009#post286009))

- **[M&R Software](http://www.m-r-software.de/)** - Original developers of OMSI 2 & plugin system, [plugin system wiki page](http://wiki.omnibussimulator.de/omsiwikineu.de/index.php?title=Plug-in-Schnittstelle) and [plugin system C++ tutorial](http://wiki.omnibussimulator.de/omsiwikineu.de/index.php?title=OMSI_Plugin_Framework)

- **[Ixe1](https://github.com/Ixe1)** - Alpha testing, UI inspiration, suggestions

- **[MrChips](https://fellowsfilm.com/members/mrchips.3079/#resources)**, **[Zeldieralt](https://fellowsfilm.com/members/zeldier.6616/)**, **[volvorider](https://reboot.omsi-webdisk.de/community/user/9681-volvorider/)**, yacho - Alpha testing

- The **[SimpleINI](https://github.com/brofield/simpleini)** project for a simple initialisation file library

- The **[Interactive Delphi Reconstructor](https://github.com/crypto2011/IDR)** project for making reverse-engineering OMSI 2 much easier

- **[Icons8](https://icons8.com/)** for allowing free usage of their icons with attribution

- For YouTube Video speciifc acknowledgements, please refer to the description of the **[YouTube video](https://www.youtube.com/watch?v=YrbM-jaZYls)**.

‎
## Disclaimer:

This software is provided "As is", without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose and noninfringement. **I cannot be held personally responsible if usage of this software results in loss of work or breakage of your OMSI 2 installation**.