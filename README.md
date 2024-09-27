<table border="0">
  <tr>
    <td align="left" valign="middle">
    <h1>EFR32 Amazon Sidewalk Application Examples</h1>
  </td>
  <td align="left" valign="middle">
    <a href="https://www.silabs.com/wireless/wi-fi">
      <img src="http://pages.silabs.com/rs/634-SLU-379/images/WGX-transparent.png"  title="Silicon Labs Gecko and Wireless Gecko MCUs" alt="EFM32 32-bit Microcontrollers" width="250"/>
    </a>
  </td>
  </tr>
</table>

# Silicon Labs Amazon Sidewalk Applications #

The Silicon Labs Amazon Sidewalk stack allows for a wide variety applications to be built on its foundation. This repo showcases some example applications built using the Silicon Labs Amazon Sidewalk stack.

## Examples ##

- [Amazon Sidewalk SoC EM4 Sleep](https://github.com/SiliconLabs/amazon-sidewalk-examples/tree/main/amazon_sidewalk_soc_em4_sleep): An example to show how to implement a switch to EM4 sleep mode while running the Amazon Sidewalk stack.

## Add the 'Amazon Sidewalk Applications' Repository to Simplicity Studio 5 ##

1. Download and install [Simplicity Studio 5](https://www.silabs.com/developers/simplicity-studio).
2. On Simplicity Studio 5, go to **Window -> Preferences -> Simplicity Studio -> External Repos**.
3. Click **[Add]**. In the **URI** field, copy & paste the following link: `https://github.com/SiliconLabs/amazon-sidewalk-examples.git`
4. Click **[Next]** then **[Finish]** and **[Apply and Close]**.

## Create the Amazon Sidewalk Applications Example Projects ##

1. Connect the Silicon Labs Starter Kit and open Simplicity Studio 5.
2. Select the **[Launcher]** perspective.
3. From the **[Debug Adapters]** panel on the left top corner, select your Silicon Labs Starter Kit.
4. Ensure that an SDK is selected in the **[General Information]** tile of the **[Overview]** tab.
5. Select the **[EXAMPLE PROJECTS & DEMOS]** tab in **[Launcher]** perspective.
6. Under **Provider** (at the bottom of the list), select **amazon-sidewalk-examples** and click **[create]** on the desired project.
   * If the project you are looking for is not listed in **amazon-sidewalk-examples**, it is possible that your debug adapter is not listed as compatible with the application. Try using a Silicon Labs debug adapter first, and check if it is listed in the project's **boardCompatibility** section of [templates.xml](templates.xml).

## Documentation ##

- Official Amazon Sidewalk documentation can be found in [the Amazon Sidewalk pages on docs.silabs.com](https://docs.silabs.com/amazon-sidewalk/latest/sidewalk-start/).
- Project-specific information is provided in the **README.md** file in each project folder.

## Reporting Bugs/Issues and Posting Questions and Comments ##

To report bugs in the Amazon Sidewalk Application Examples projects, please create a new "Issue" in the "Issues" section of this repo. Please reference the board, project, and source files associated with the bug, and reference line numbers. If you are proposing a fix, also include information on the proposed fix. Since these examples are provided as-is, there is no guarantee that these examples will be updated to fix these issues.

Questions and comments related to these examples should be made by creating a new "Issue" in the "Issues" section of this repo.

## Disclaimer ##

The Gecko SDK suite supports development with Silicon Labs IoT SoC and module devices. Unless otherwise specified in the specific directory, all examples are considered to be EXPERIMENTAL QUALITY which implies that the code provided in the repos has not been formally tested and is provided as-is.  It is not suitable for production environments.  In addition, this code will not be maintained and there may be no bug maintenance planned for these resources. Silicon Labs may update projects from time to time.