# CoffeeSave
Version of DefSave module with JS-side obfuscation
A module to help you save / load config and player data in your Defold projects between sessions

## Installation
You can use CoffeeSave in your own project by adding this project as a [Defold library dependency](http://www.defold.com/manuals/libraries/). Open your game.project file and in the dependencies field under project add:

	https://github.com/coffee-lady/CoffeeSave/archive/master.zip

Once added, you must require the main Lua module in scripts via

```
local CoffeeSave = require("CoffeeSave.CoffeeSave")
```

## Usage

First set your game's appname

```
CoffeeSave.appname = "my_awesome_game"
```

Load a file

```
CoffeeSave.load("config")
```

Get a key from a loaded file

```
CoffeeSave.get("config", "audio")
```

Set a key to a loaded file

```
CoffeeSave.set("config", "fullscreen", false)
```

Save a file

```
CoffeeSave.save("config")
```

You can save all files at once. By default, it will only actually save files with changes, but you can force saving all files by setting the force flag to true.

```
CoffeeSave.save_all() -- only saves changed files
```
```
CoffeeSave.save_all(true) -- saves all files
```

In your update, if you want autosave to be enabled, you will need to include

```
CoffeeSave.update(dt)
```

To save all files on the ending of your game you need to include in final

```
CoffeeSave.save_all()
```

You can setup template defaults for your files too. These are used if you set CoffeeSave.use_default_data to true which is true by default. While use_default_data is true CoffeeSave will check the CoffeeSave.default_data table to see if there is any default data there when a file is loaded which is empty. Check the example for an example of default_data.lua and how it can be set.

## Information

Don't include an extension in your file names. Use "config" over "config.dat" for example.

Don't name your filenames with a leading number or any character not allowed in Lua variable names. Use "profile_1" not "1" for example.

By default, the contents of the saved files are not encrypted, but support for this is coming soon.

Set verbose to true to also print any successful messages, otherwise only errors or warnings will be printed.
