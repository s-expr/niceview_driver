{
  description = "A basic flake with a shell";
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  inputs.flake-utils.url = "github:numtide/flake-utils";
  inputs.esp-idf.url = "github:mirrexagon/nixpkgs-esp-dev";

  outputs =
    { nixpkgs, flake-utils, esp-idf, ... }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        extraPkgs = with pkgs; [
          gdbgui
          nodejs_24
          pulseview
          bear
          jq
        ];
        toolchain = esp-idf.packages.${system}.esp-idf-xtensa;
        stdenv = esp-idf.packages.${system}.esp-idf-xtensa.tools.xtensa-esp-elf;
        shell = esp-idf.devShells.${system}.esp-idf-full.overrideAttrs (default: {
            nativeBuildInputs = default.nativeBuildInputs ++ extraPkgs;
            buildInputs = default.buildInputs ++ extraPkgs;
        });
      in
      {
        toolchain = toolchain;
        shell = shell;
        devShells.default = pkgs.mkShellNoCC {
            inputsFrom = [ shell ];
            IDF_TOOLCHAIN="gcc";
            IDF_TARGET="esp32s3";
            shellHook = (default.shellHook or "") + ''
            export CLANGD_QUERY_DRIVER="$(which clang),$(which clang++)"
                cat > .clangd <<EOF
CompileFlags:
  CompilationDatabase: build.clang/
  Add:
    - -isystem
    - ${stdenv}/xtensa-esp-elf/xtensa-esp-elf/include/
EOF
'';
        };
      }
    );
}
