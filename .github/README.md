# OMSI Presentation Tools

<div align="center">

![SCREENSHOT](https://github.com/sjain882/OMSI-Presentation-Tools/blob/main/.github/Preview.png?raw=true)

[![ISSUES](https://img.shields.io/github/issues/sjain882/OMSI-Presentation-Tools?color=FF6D00&style=flat)](https://github.com/sjain882/OMSI-Presentation-Tools/issues)
[![VERSION](https://img.shields.io/github/v/release/sjain882/OMSI-Presentation-Tools?color=FF6D00&style=flat&label=version)](https://github.com/sjain882/OMSI-Presentation-Tools/releases/latest)
[![YOUTUBE TUTORIAL](https://img.shields.io/badge/-YouTube%20Tutorial-%23BF360C)](https://www.youtube.com/watch?v=YrbM-jaZYls)
[![STEAM GUIDE](https://img.shields.io/badge/-Steam%20Guide-%2301579B?style=flat)](https://steamcommunity.com/sharedfiles/filedetails/?id=2722795667)
[![DOWNLOAD](https://img.shields.io/badge/-Download-%232E7D32?style=flat)](https://github.com/sjain882/OMSI-Presentation-Tools/releases/latest)

Assorted tools to aid the creation of high-quality screenshots & videos for [OMSI 2](https://store.steampowered.com/app/252530).

Currently in very early stages.
</div>

‎
## Features:

- Compatibility with OMSI 2 v2.2.032 ("Tram compatible" patch) and v2.3.004 (latest version)
- Toggle overriding of the FoV (Field-of-View) of the Free Map (F4) Camera to a custom value (1.0-150.0°)
- Works when multiple instances of OMSI 2 are running (don't ask why, it **[just works™](https://github.com/sjain882/OMSI-Presentation-Tools/raw/main/.github/Multi-instance.png?raw=true)**)
- Can be injected into Omsi.exe (saves relaunching OMSI if you forgot to install - can take up to 10 mins on larger installs)

‎
## Planned features (hopefully):

- Ability to toggle overriding of the FOV, angles, positioning & (probably not) roll of all cameras
- Ability to save modified camera attributes to `*.bus` & `*.ovh` files
- Ability to use the F4 camera as a free-roam/look camera
- Ability to define pre-defined camera movement sequences (**[HLAE](https://github.com/advancedfx/advancedfx)**-like) in text format
- Ability to toggle overriding of bus presentation variables such as dirt, wetness, physics/roll etc
- Ability to speedhack (slow/fast) the game - Cheat Engine's speedhack does not work properly with OMSI 2 
- Ability to spawn several morphable & movable chromakeys & toggle between red, blue & green colours
- (Likely never) TrackIR integration for any free roam camera, if achieved

‎
## Important!

###### Anti-cheat warning

- Due to the nature of this tool, it is possible some game anti-cheats will flag this software. 

- Thus, **please ensure you keep all games which have anti-cheats closed while running OMSI 2 with OMSI Presentation Tools.** 

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
- Closing the thread doesn't fully detach it, it just gets rid of the UI and stops the main program loop. Not a major issue, but not graceful or proper. Can fix this when I learn more about multithreading.

‎
## FAQ:

**Q:** Why didn't you put the GUI in an overlay for OMSI 2 instead of having an extra window floating around?

**A:** OMSI 2 is already a pretty unstable game. A host of compatibility issues with game overlays (NVIDIA Share, Discord, Steam) need to be considered when adding your own overlay. As well as this, users may be using either the stock DX9 game, DX12PY (DX12) or DXVK (Vulkan), and may be using SweetFX, ENB or ReShade combined with either of those. This is simply too many combinations to consider and is not a valuable use of my time. No need to add potential instability or unnecessary resource usage for such a simple tool right now.

‎
## Building:

There is no specific build process. Simply install Visual Studio Community (I used 2019) with C++ Desktop and [CLR Workloads](https://www.youtube.com/watch?v=HcxlYkU8aY0) support, clone this repo, open the solution (`*.sln`) file, set the Configuration to Release x86 and run Build > Build solution.

You might need to remove my post-build event from Solution Properties > Build Events > Post-Build event (Visual Studio 2019).

Lower versions of Visual Studio should work, but I used VS 2019 with the C++17 language standard.

‎
## Thanks to:

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