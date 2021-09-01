# Micro-Turbojet Test Rig

This repository contains all the files created during my thesis, Test Rig Design for a Micro-Turbojet Engine. More information about these contents, designs and uses can be found in the document of the thesis.

Different parts of the test rig design where explored during the project, these are sepparated into folders with the same topic. The explanation of this organization and a brief explanation of each subproject can be found below.


### Contents

+ [StructureDesign](#-structuredesign---structuredesign-): Autodesk Inventor project
	+ Bellmouth: Parts, drawings and final files
	+ CommercialParts
	+ DesignedParts: Parts and drawings
+ [DataAcquisitionMCs](#-dataacquisitionmcs---dataacquisitionmcs-): MPLAB X projects
	+ Pressure
	+ Temperature
	+ Thrust_Flow
+ [DataProcessingMaster](#-dataprocessingmaster---dataprocessingmaster-): Python files and classes
+ [PCBDesigns](#-pcbdesigns---pcbdesigns-): Autodesk Eagle projects
	+ RTD_conditioning
	+ System_control
	+ General_board


## [StructureDesign](./StructureDesign)

This folder contains the Autodesk Inventor files of the designed bench. the bench features both [commercial parts](./StructureDesign/CommercialParts) and [designed parts](./StructureDesign/DesignedParts). The design of a [bellmouth](./StructureDesign/Bellmouth) is also included.

All the designed components have their corresponding sketches in DWG, DXF and PDF formats so that they can be manufactured. The bellmouth is expected to be 3D printed, therefore, STL files are profided along with the sketches. The links to the commercial parts can be found in the budget of the project (document).

## [DataAcquisitionMCs](./DataAcquisitionMCs)

Here the MPLAB X projects can be found. Files are coded in C and are divided into 3 projects (each one corresponding to a microcontroller):
+ Pressure
+ Temperature
+ Thrust_Flow

In order to program the microcontrollers it is necessary to open the projects in the MPLAB X IDE, compile them and then transfer them to the mCs through a USB cable.


## [DataProcessingMaster](./DataProcessingMaster)

This folder contains the Python files and classes necessary to program the Raspberry Pi 4 that acts as master. This master connects to the microcontrollers in order to gather data and save it to a database.

All the files must be saved into the `Turbojet` folder (as they are organized) inside the Raspberry Pi 4 in order to function properly. More information about how the program works and how to modify it can be found in the document.


## [PCBDesigns](./PCBDesigns)

Three boards are designed to hold all the electronics together. Autodesk Eagle is used to create these and their projects can be found inside this folder. Boards are:
+ An RTD PT100 circuit board
+ A control board
+ A base board to hold all conditioning boards


