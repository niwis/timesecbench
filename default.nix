with import <nixpkgs> {};

 # Make a new "derivation" that represents our shell
stdenv.mkDerivation {
  name = "apps_builder";

  # The packages in the `buildInputs` list will be added to the PATH in our shell
  buildInputs = with pkgs; [
    python3
    pythonPackages.click
    pythonPackages.pyelftools
    bash
  ];
}
