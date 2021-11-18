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
</div>

‎
## Features:

- Ability to change the FOV (Field-of-View) of the Free Map (F4) Camera (1.0-150.0°)

‎
## Planned features (hopefully):

- Ability to change the FOV, angles, roll & positioning of all cameras in the game scene
- Ability to save modified camera attributes to `*.bus` & `*.ovh` files
- Ability to use the F4 camera as a free-roam/look camera via D3D9 Matrix manipulation
- Ability to define pre-defined camera movement sequences (**[HLAE](https://github.com/advancedfx/advancedfx)**-like) in text format
- Ability to toggle override of bus presentation variables such as dirt, wetness, etc
- Ability to spawn several morphable & movable chromakeys & toggle between red, blue & green colours
- (Likely never) TrackIR integration for any free roam camera, if achieved
- (Likely never) move all UI into a fully compatible ImGui overlay directly in OMSI 2

‎
## Important!

- Due to the nature of this app, it is possible some game anti-cheats will flag this software. 

- Thus, **please ensure you keep all other games closed while running OMSI 2 with OMSI Presentation Tools, especially if they have an anti-cheat.** 

- In theory there should be no issues since this tool restricts itself to memory regions OMSI has read-access to, but its possible it could be flagged up. The same applies to antivirus detections.

- Although all of these cases are extremely unlikely, if not impossible, please note that **I cannot be held personally responsible (directly or indirectly)** if usage of this tool results in an anti-cheat ban in other games, the breaking of your OMSI install or other software, or loss of data.

‎
## Installation & usage:

1. Click **[here](https://github.com/sjain882/OMSI-Telemetry/releases/latest)** to download the archive with the required files.

2. Open the downloaded archive with File Explorer / Windows Explorer.

3. Ensure OMSI 2 is **not running**.

4. Open the **_OMSI 2_** folder.

5. Copy the contents inside.

6. Open Steam.

7. Hover your cursor over the **_Library_** tab in the top left, then click on **_Home_**.

8. Right click on the **_OMSI 2_** entry in the games list on the left.

9. Click on **_Properties..._**.

10. Click on the **_Local Files_** option on the left.

11. Click on _**Browse...**_. A File Explorer / Windows Explorer window will appear.

12. Paste the contents into this location and click **_Replace the files in the destination_** (or similar) if prompted.

13. Close any other games you have running, especially if they use anti-cheat software.

14. Launch OMSI 2. OMSI Presentation Tools will automatically initialise once OMSI's loading screen appears.

**[YouTube tutorial & suggested usage](https://www.youtube.com/watch?v=pvU8gO66mTs)**

‎
## Known issues:

- Will break if multiple instances of OMSI 2 are running simultaneously.
- Potential anti-cheat & anti-virus incompatibilities.

‎
## Changelog of updates:

###### v0.1.0 alpha:

- Initial release

‎
## Thanks to:

- **[rev_eng_e](https://github.com/rev_eng_e)** - Array of Byte (AoB) pattern scanner code

- **[win32kbase / Wolfie](https://github.com/win32kbase)** - assistance with reverse engineering of OMSI executable

- **[M&R Software](http://www.m-r-software.de/)** - Original developers of OMSI 2 & plugin system, [plugin system wiki page](http://wiki.omnibussimulator.de/omsiwikineu.de/index.php?title=Plug-in-Schnittstelle) and [plugin system C++ tutorial](http://wiki.omnibussimulator.de/omsiwikineu.de/index.php?title=OMSI_Plugin_Framework)

***

<div align="center">
Written with ♥️ in C++.
</div>