{
  description = "Arduino + VSCode + Arduino Maker Workshop dev environment";

  inputs = {
    nixos-config.url = "github:BerndDonner/NixOS-Config";
    nixpkgs.follows = "nixos-config/nixpkgs";
  };

  outputs = { self, nixpkgs, nixos-config, ... }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs {
        inherit system;
        config.allowUnfree = true;
        overlays = [
          nixos-config.overlays.unstable
        ];
      };

      # 🧩 Arduino shell template from your nixos-config lib
      arduinoDev = import (nixos-config + "/lib/arduino-develop.nix");
    in
    {
      devShells.${system} = {
        # ---------------------------------------------------------
        # 1️⃣ Default shell – VSCode + Arduino Maker Workshop
        # ---------------------------------------------------------
        default = arduinoDev {
          inherit pkgs;
          inputs = { inherit nixos-config nixpkgs; };
          checkInputs = [ "nixos-config" ];
          flakeLockPath = ./flake.lock;

          symbol = "📟";
          message = "📟 VSCode + Arduino Maker Workshop environment ready";

          extraPackages = with pkgs; [
            vscode-fhs
          ];
        };

        # ---------------------------------------------------------
        # 2️⃣ CLI shell – Helix + simavr + arduino-cli
        # ---------------------------------------------------------
        cli = arduinoDev {
          inherit pkgs;
          inputs = { inherit nixos-config nixpkgs; };
          checkInputs = [ "nixos-config" ];
          flakeLockPath = ./flake.lock;

          symbol = "🔧";
          message = "🔧 CLI Arduino environment (helix, simavr, arduino-cli) ready";

          extraPackages = with pkgs; [
            simavr
            pkgsCross.avr.buildPackages.gdb
            pkgsCross.avr.buildPackages.gcc
          ];

          extraShellHook = ''
            echo "Using Helix + simavr + arduino-cli toolchain"
          '';
        };
      };
    };
}
