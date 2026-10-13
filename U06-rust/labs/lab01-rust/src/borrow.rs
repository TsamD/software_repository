fn main() {
    let mut v = vec![1, 2, 3];
    let first = &v[0];      // emprunt immuable
    v.push(4);              // emprunt mutable simultane -> ERREUR
    println!("{}", first);
}
