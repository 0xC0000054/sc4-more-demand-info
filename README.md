# sc4-more-demand-info

A DLL Plugin for SimCity 4 that provides more game variables with RCI demand information.   

With this plugin installed there will be the following new variables that can be used from LUA scripts and UI files:

| Variable name  | Description |
|-----------------------|-------------|
| `g_cs1_active_demand` | Cs§ active demand |
| `g_cs1_demand` | Cs§ demand |
| `g_cs2_active_demand` | Cs§§ active demand |
| `g_cs2_demand` | Cs§§ demand |
| `g_cs3_active_demand` | Cs§§§ active demand |
| `g_cs3_demand` | Cs§§§ demand |
| `g_ir_active_demand`  | IR (I-Ag) active demand |
| `g_ir_demand`  | IR (I-Ag) demand |
| `g_current_ir_cap`    | Current IR (I-Ag) cap |
| `g_id_demand` | ID demand |
| `g_im_demand` | IM demand |
| `g_iht_demand` | IHT demand |

The values can be accessed using `game.<value name>` in LUA scripts and UI placeholder text.

The plugin can be downloaded from the Releases tab: https://github.com/0xC0000054/sc4-more-demand-info/releases

## System Requirements

* Windows 10 or later
The plugin may work on Windows 7 or later with the [Microsoft Visual C++ 2022 x86 Redistribute](https://aka.ms/vs/17/release/vc_redist.x86.exe) installed, but I do not have the ability to test that.

## Installation

1. Close SimCity 4.
2. Copy `SC4MoreDemandInfo.dll` into the Plugins folder in the SimCity 4 installation directory.
3. Start SimCity 4.

## Troubleshooting

The plugin should write a `SC4MoreDemandInfo.log` file in the same folder as the plugin.    
The log contains status information for the most recent run of the plugin.

# License

This project is licensed under the terms of the MIT License.    
See [LICENSE.txt](LICENSE.txt) for more information.

## 3rd party code

[gzcom-dll](https://github.com/nsgomez/gzcom-dll/tree/master) Located in the vendor folder, MIT License.    
[Windows Implementation Library](https://github.com/microsoft/wil) MIT License    

# Source Code

## Prerequisites

* Visual Studio 2022

## Building the plugin

* Open the solution in the `src` folder
* Update the post build events to copy the build output to you SimCity 4 application plugins folder.
* Build the solution

## Debugging the plugin

Visual Studio can be configured to launch SimCity 4 on the Debugging page of the project properties.
I configured the debugger to launch the game in a window with the following command line:    
`-intro:off -CPUcount:1 -w -CustomResolution:enabled -r1920x1080x32`

You may need to adjust the resolution for your screen.
