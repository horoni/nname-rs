#![allow(non_snake_case)]

use {clap::Parser, std::io::Write};

#[derive(Parser, Debug)]
#[clap(author, version, about, long_about = None)]
struct Args {
    nickname: String,
    #[clap(short = 'p', default_value_t)]
    prefix: String,
    #[clap(short = 'P', default_value_t)]
    postfix: String,
    #[clap(short = 'o', action)]
    oflag: bool,
    #[clap(short = 'O', action)]
    Oflag: bool,
    #[clap(short = 'b', action)]
    bflag: bool,
    #[clap(short = 'd', action)]
    dflag: bool,
}

fn main() -> std::io::Result<()> {
    let args = Args::parse();

    if args.oflag {
        print!("{}", args.prefix);
    }
    for c in args.nickname.into_bytes() {
        if !args.oflag {
            print!("{}", args.prefix);
        }
        if args.bflag {
            print!("{:08b}", c);
        } else if args.Oflag {
            print!("{:03o}", c);
        } else if args.dflag {
            print!("{}", c);
        } else {
            print!("{:02x}", c);
        }
        if !args.oflag {
            print!("{} ", args.postfix);
        }
    }
    if args.oflag {
        print!("{}", args.postfix);
    }
    print!("\n");
    std::io::stdout().flush()?;
    Ok(())
}
