fn main() {
    let out_dir = "src/pb";
    std::fs::DirBuilder::new()
        .recursive(true)
        .create(out_dir)
        .unwrap();

    prost_build::Config::new()
        .out_dir(out_dir)
        .compile_protos(&["abi.proto"], &["."])
        .unwrap();
}