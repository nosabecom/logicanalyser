"""Expose the ESP32 SDK response-file includes to PlatformIO's IDE index."""

from pathlib import Path
import shlex

Import("env", "projenv")

# GCC reads these paths through -iprefix and @flags/includes, but IntelliSense
# needs explicit include paths. Only change IDE metadata, not compiler flags.
if env.IsIntegrationDump():
    sdk_dir = Path(
        env.PioPlatform().get_package_dir("framework-arduinoespressif32-esp32-libs")
    )
    flags = shlex.split((sdk_dir / "flags" / "includes").read_text(encoding="utf-8"))
    projenv.AppendUnique(
        CPPPATH=[
            str(sdk_dir / "include" / flags[index + 1])
            for index, flag in enumerate(flags[:-1])
            if flag == "-iwithprefixbefore"
        ]
    )
