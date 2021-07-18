/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the FOO module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
// Component
function Component()
{
    // default constructor
}
// createOperations
Component.prototype.createOperations = function()
{
    // call default implementation to actually install GalaxyCalculator.exe!
    component.createOperations();
    /* ************************************************************************
       productType: "windows", "opensuse", "osx"
       productVersion: "7" for Windows 7, "13.2" for openSUSE 13.2, "10.8" for OS X Mountain Lion
    */    
    if (systemInfo.productType === "windows") 
    {
        component.addOperation("CreateShortcut", "@TargetDir@/Galaxy-Calculator-2.exe", "@StartMenuDir@/Galaxy-Calculator-2.lnk",
            "workingDirectory=@TargetDir@", "iconPath=%SystemRoot%/system32/SHELL32.dll", "iconId=2", 
            "description=Galaxy Calculator 2 by the Light Wizzard");
    }
    /* ************************************************************************
        currentCpuArchitecture:"i386" "x86_64"
        installer.value("os") === "x11"
        systemInfo.kernelTypes: linux, darwin, winnt
    */   
    if (systemInfo.kernelType === "linux")
    {
	    component.addOperation( "InstallIcons", "@TargetDir@/icons" );
        component.addOperation("CreateDesktopEntry", "@TargetDir@/Galaxy-Calculator-2.desktop", "Version=1.0\nType=Application\nTerminal=false\nExec=@TargetDir@/Galaxy-Calculator-2-x86_64.AppImage\nName=Galaxy-Calculator-2\nIcon=@TargetDir@/Galaxy-Calculator-2.svg\nName[en_US]=Galaxy-Calculator-2.desktop");
        component.addElevatedOperation("Copy", "@TargetDir@/Galaxy-Calculator-2.desktop", "@HomeDir@/Desktop/Galaxy-Calculator-2.desktop");
    }
    if (systemInfo.kernelType === "darwin")
    {
	    component.addOperation( "InstallIcons", "@TargetDir@/icons" );
        component.addOperation("CreateDesktopEntry", "@TargetDir@/Galaxy-Calculator-2.desktop", "Version=1.0\nType=Application\nTerminal=false\nExec=@TargetDir@/Galaxy-Calculator-2-x86_64.AppImage\nName=Galaxy-Calculator-2\nIcon=@TargetDir@/Galaxy-Calculator-2.svg\nName[en_US]=Galaxy-Calculator-2.desktop");
        component.addElevatedOperation("Copy", "@TargetDir@/Galaxy-Calculator-2.desktop", "@HomeDir@/Desktop/Galaxy-Calculator-2.desktop");
    }
} // end createOperations
// End of File
