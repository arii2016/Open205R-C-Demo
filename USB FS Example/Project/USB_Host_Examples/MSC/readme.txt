/**
  @page USBH_MSC  USB Host MSC example
  
  @verbatim
  ******************** (C) COPYRIGHT 2011 STMicroelectronics *******************
  * @file    readme.txt 
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    22-July-2011
  * @brief   Description of the USB Host MSC example
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
   @endverbatim

   
@par Example Description 

This example provides a description of how to use the USB OTG host peripheral 
on the STM32F2xx and STM32F105/7 devices.

The STM32 behave as a mass storage Host that can enumerate, show content and display
the supported BMP image in the attached USB flash disk.
When the user press the user key button [B4], the application explore the USB flash
disk content and display it on the LCD. The user has to press the user key button
to display the whole disk flash (recursion level 2).
Once the entire disk flash content is explored, the user has to press the user key
button to write a small file (less to 1 KB) on the disk.
After writing the file to the disk, the user can press the user key button and start 
the Image slide show (BMP file located in the USB Disk root).
Once all the images are displayed, the application explores again the disk flash.

 @note Only the BMP files with the following format are supported : 
         - width  : 320
         - Height : 240
         - BPP    :  16
         - Compression : RGB bitmap with RGB masks  
       To use the Image browser, copy the BMP files from "\Utilities\Binary\Media"
       to the root of the USB flash disk to be used. 
       
This example works
  - in high speed (HS) when the STM322xG-EVAL board and the USB OTG HS peripheral are used
  - in full speed (FS) when the STM322xG-EVAL board and the USB OTG FS peripheral are used 
    or when using the STM3210C-EVAL board.


@par Hardware and Software environment 

   - This example runs on STM32F105/7 Connectivity line and STM32F2xx devices.
  
   - This example has been tested with STM3210C-EVAL RevB (STM32F105/7 devices) 
     and STM322xG-EVAL RevB (STM32F2xx)    

  - STM3210C-EVAL Set-up 
    - Use CN2 connector to connect the board to a PC host or USB device

  - STM322xG-EVAL Set-up
    - Use CN8 connector to connect the board to a PC host when using USB OTG FS peripheral.
    - Use CN9 connector to connect the board to a PC host when using USB OTG HS peripheral.    


@par How to use it ?

 + EWARM
    - Open the USBH_MSC.eww workspace.
    - In the workspace toolbar select the project config:
     - STM322xG-EVAL_USBH-HS: to configure the project for STM32F2xx devices and use USB OTG HS peripheral
     - STM322xG-EVAL_USBH-FS: to configure the project for STM32F2xx devices and use USB OTG FS peripheral
     - STM3210C-EVAL_USBH-FS: to configure the project for STM32F105/7 devices  
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)

 + MDK-ARM
    - Open the USBH_MSC.uvproj project
    - In the build toolbar select the project config:
     - STM322xG-EVAL_USBH-HS: to configure the project for STM32F2xx devices and use USB OTG HS peripheral
     - STM322xG-EVAL_USBH-FS: to configure the project for STM32F2xx devices and use USB OTG FS peripheral
     - STM3210C-EVAL_USBH-FS: to configure the project for STM32F105/7 devices  
    - Rebuild all files: Project->Rebuild all target files
    - Load project image: Debug->Start/Stop Debug Session
    - Run program: Debug->Run (F5)    

 + RIDE
    - Open the USBH_MSC.rprj project.
    - In the configuration toolbar(Project->properties) select the project config:
     - STM322xG-EVAL_USBH-HS: to configure the project for STM32F2xx devices and use USB OTG HS peripheral
     - STM322xG-EVAL_USBH-FS: to configure the project for STM32F2xx devices and use USB OTG FS peripheral
     - STM3210C-EVAL_USBH-FS: to configure the project for STM32F105/7 devices  
    - Rebuild all files: Project->build project
    - Load project image: Debug->start(ctrl+D)
    - Run program: Debug->Run(ctrl+F9)

 + TASKING
    - Open TASKING toolchain.
    - Click on File->Import, select General->'Existing Projects into Workspace' 
      and then click "Next". 
    - Browse to  TASKING workspace directory and select the project: 
     - STM322xG-EVAL_USBH-HS: to configure the project for STM32F2xx devices and use USB OTG HS peripheral
     - STM322xG-EVAL_USBH-FS: to configure the project for STM32F2xx devices and use USB OTG FS peripheral
     - STM3210C-EVAL_USBH-FS: to configure the project for STM32F105/7 devices  
    - Under Windows->Preferences->General->Workspace->Linked Resources, add 
      a variable path named "Cur_Path" which points to the folder containing
      "Libraries", "Project" and "Utilities" folders.
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Select the project in the "Project explorer" window then click 
      Run->Debug (F11)

 + TrueSTUDIO
    - Open the TrueSTUDIO toolchain.
    - Click on File->Switch Workspace->Other and browse to TrueSTUDIO workspace 
      directory.
    - Click on File->Import, select General->'Existing Projects into Workspace' 
      and then click "Next". 
    - Browse to the TrueSTUDIO workspace directory and select the project:  
     - STM322xG-EVAL_USBH-HS: to configure the project for STM32F2xx devices and use USB OTG HS peripheral
     - STM322xG-EVAL_USBH-FS: to configure the project for STM32F2xx devices and use USB OTG FS peripheral
     - STM3210C-EVAL_USBH-FS: to configure the project for STM32F105/7 devices  
    - Under Windows->Preferences->General->Workspace->Linked Resources, add 
      a variable path named "CurPath" which points to the folder containing
      "Libraries", "Project" and "Utilities" folders.
    - Rebuild all project files: Select the project in the "Project explorer" 
      window then click on Project->build project menu.
    - Run program: Select the project in the "Project explorer" window then click 
      Run->Debug (F11)
    
@note Known Limitations
      This example retargets the C library printf() function to the EVAL board’s LCD
      screen (C library I/O redirected to LCD) to display some Library and user debug
      messages. TrueSTUDIO Lite version does not support I/O redirection, and instead
      have do-nothing stubs compiled into the C runtime library. 
      As consequence, when using this toolchain no debug messages will be displayed
      on the LCD (only some control messages in green will be displayed in bottom of
      the LCD). To use printf() with TrueSTUDIO Professional version, just include the
      TrueSTUDIO Minimal System calls file "syscalls.c" provided within the toolchain.
      It contains additional code to support printf() redirection.
    
 * <h3><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h3>
 */
