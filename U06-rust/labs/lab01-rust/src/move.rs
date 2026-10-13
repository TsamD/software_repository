fn main() {
    let s = String::from("secret");
    let t = s;              // ownership deplace vers t
    println!("{}", s);      // ERREUR : s n'est plus valide
}
