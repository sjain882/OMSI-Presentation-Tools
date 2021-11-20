# OMSI Presentation Tools

<div align="center">

![SCREENSHOT](https://github.com/sjain882/OMSI-Presentation-Tools/blob/main/Preview.png?raw=true)

[![ISSUES](https://img.shields.io/github/issues/degeneratehyperbola/NEPS?color=orange&label=Issues&style=plastic)](https://github.com/degeneratehyperbola/NEPS/issues)
[![VERSION](https://img.shields.io/github/v/release/degeneratehyperbola/NEPS?color=orange&label=Version&style=plastic)](https://github.com/degeneratehyperbola/NEPS/releases/latest)
[![LICENSE](https://img.shields.io/badge/License-BSD%203--Clause%20Modified-orange?style=plastic)](https://github.com/degeneratehyperbola/NEPS/blob/master/LICENSE.md)
[![STAR](https://img.shields.io/badge/%20-Star%20this%20project!-orange?style=plastic)](https://upload.wikimedia.org/wikipedia/commons/thumb/f/f1/Heart_coraz%C3%B3n.svg/1200px-Heart_coraz%C3%B3n.svg.png)
[![YOUTUBE](https://img.shields.io/badge/%20-Trailer-orange?style=plastic)](https://www.youtube.com/watch?v=pvU8gO66mTs)
[![DOWNLOAD](https://img.shields.io/badge/%20-Download-orange?style=plastic)](https://github.com/degeneratehyperbola/NEPS/releases/latest)

Assorted tools to aid the creation of high-quality screenshots & videos for [OMSI 2](https://store.steampowered.com/app/252530).

Currently in very early stages.
</div>

‎
## Features:

- Ability to toggle overriding of the FOV (Field-of-View) of the Free Map (F4) Camera (1.0-150.0°)

‎
## Planned features (hopefully):

- Ability to toggle overriding of the FOV, angles, roll & positioning of all cameras present in the game scene
- Ability to save modified camera attributes to `*.bus` & `*.ovh` files
- Ability to use the F4 camera as a free-roam/look camera via D3D9 Matrix manipulation
- Ability to define pre-defined camera movement sequences (**[HLAE](https://github.com/advancedfx/advancedfx)**-like) in text format
- Ability to toggle overriding of bus presentation variables such as dirt, wetness, etc
- Ability to spawn several morphable & movable chromakeys & toggle between red, blue & green colours
- (Likely never) TrackIR integration for any free roam camera, if achieved
- (Likely never) move all UI into a fully compatible ImGui overlay directly in OMSI 2

‎
## Important!

- Due to the nature of this tool, it is possible some game anti-cheats will flag this software. 

- Thus, **please ensure you keep all other games closed while running OMSI 2 with OMSI Presentation Tools, especially if they have an anti-cheat.** 

- In theory there should be no issues since this tool restricts itself to memory regions OMSI has read-access to, but its possible it could be flagged up. The same applies to antivirus detections.

- Although all of these cases are extremely unlikely, if not impossible, please note that **I cannot be held personally responsible (directly or indirectly)** if usage of this tool results in an anti-cheat ban in other games, the breaking of your OMSI install or other software, or loss of data.

- Users will be reminded of all this information via a pop-up message box upon first launch of the tool (only).

‎
## Installation & usage:

**[YouTube tutorial & suggested usage](https://www.youtube.com/watch?v=pvU8gO66mTs)**

‎
## Known issues:

- Will break if multiple instances of OMSI 2 are running simultaneously.
- Potential anti-cheat & anti-virus incompatibilities.
- Entire UI has hardcoded coordinates and doesn't DPI scale. The way of using C++ Windows Forms here is a little broken in Visual Studio 2019, some methods just aren't recognised in the assembly... will eventually move from C++ WinForms to a simple C++ plugin that calls C# WPF or Windows Forms.

‎
## FAQ:

**Q:** Why didn't you put the GUI in an overlay for OMSI 2 instead of having an extra window floating around?

**A:** OMSI 2 is already a pretty unstable game. A host of compatibility issues with game overlays (NVIDIA Share, Discord, Steam) need to be considered when adding your own overlay. As well as this, users may be using either the stock DX9 game, DX12PY (DX12) or DXVK (Vulkan), and may be using SweetFX, ENB or ReShade combined with either of those. This is simply too many combinations to consider and is not a valuable use of my time. No need to add potential instability or unnecessary resource usage for such a simple tool right now.

‎
## Thanks to:

- **[rev_eng_e](https://github.com/rev-eng-e)** - Array of Byte (AoB) pattern scanner & execution timer code

- **[win32kbase / Wolfie](https://github.com/win32kbase)** - assistance with reverse engineering of OMSI executable

- **[M&R Software](http://www.m-r-software.de/)** - Original developers of OMSI 2 & plugin system, [plugin system wiki page](http://wiki.omnibussimulator.de/omsiwikineu.de/index.php?title=Plug-in-Schnittstelle) and [plugin system C++ tutorial](http://wiki.omnibussimulator.de/omsiwikineu.de/index.php?title=OMSI_Plugin_Framework)

- The **[SimpleINI](https://github.com/brofield/simpleini)** project for a simple initialisation file library