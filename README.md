# beam-sdk-unreal-example

A minimal working example of how to interact with the BeamClient in the beam-sdk-unreal plugin.

Note: Blueprints were created in UE 5.2.1, so only versions newer than that are likely to work.

## Setup

### Prerequisites
The [beam-sdk-unreal](https://github.com/Merit-Circle/beam-sdk-unrea) repo is included as a submodule in this git repository under /Plugins/BeamSDK/.

If no files are present in this `/Plugins/BeamSDK/` directory, run this command at the project root to pull the submodule:
> git submodule init

Some git clients automatically prompt you to pull submodules when cloning a repository. If you are using one of these clients, you may not need to run the above command.


### Unreal Setup

1. Create a DefaultSecrets.ini file in the Config directory
   1. Add this section to the file: `[/Script/BeamExample.ExampleGameInstance]`
   2. Add this line to the section: `BeamApiKey=YOUR_API_KEY`
   3. Replace `YOUR_API_KEY` with your publishable Beam API key
   4. Note: You can invent your own system for injecting the BeamApiKey, this was done to keep the key out of source control through the .gitignore.
2. Right-click the .uproject file and select "Generate Visual Studio project files"
3. Double-click the .sln file to open it in your IDE
4. Build & Run
