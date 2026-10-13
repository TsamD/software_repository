fn longest<'a>(x: &'a str) -> &'a str { x }
fn main() {
    let r;
    {
        let s = String::from("temporaire");
        r = longest(&s);    // s ne vit pas assez longtemps -> ERREUR
    }
    println!("{}", r);
}
