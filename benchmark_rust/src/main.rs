
use std::time::Instant;
use rayon::prelude::*;

static N:usize = 100000;


fn f_for(a:&Vec<f64> ,b:&Vec<f64> ,c: &mut Vec<f64> ){
    let a = &a[..a.len()];
    let b = &b[..b.len()];
    let nn = a.len();
    let c = &mut c[..nn];

    for (((i, ci),ai),bi) in c.iter_mut().enumerate().zip(a.iter()).zip(b.iter()){
        if i==0{
            *ci = ai.powf(2.0)+bi.powf(2.0)+ai*bi;

            continue;
        }
        unsafe{
            *ci = ai.powf(2.0)+b.get_unchecked(i-1).powf(2.0)+ai*bi+ai+bi;
        }
    }
}


fn f_rayon(a:&Vec<f64> ,b:&Vec<f64> ,c: &mut Vec<f64> ){
    let a = &a[..a.len()];
    let b = &b[..b.len()];
    let nn = a.len();
    let c = &mut c[..nn];

    (0..nn, c, a, b).into_par_iter().for_each(
        |(i, ci, ai, bi)|{ 
            if i==0{
                *ci = ai.powf(2.0)+bi.powf(2.0)+ai*bi;
            }else{
                unsafe{
                    *ci = ai.powf(2.0)+b.get_unchecked(i-1).powf(2.0)+ai*bi+ai+bi;
                }
            }
        });
}




fn main() {

    let mut a: Vec<f64> = Vec::with_capacity(N);
    let mut b: Vec<f64> = Vec::with_capacity(N);
    let mut c: Vec<f64> = Vec::with_capacity(N);

    for i in 0..N{
        a.push(i as f64 + 0.2174);
        b.push(i as f64 + 0.8903);
        c.push(0.0);
    }

    let n_loop = 7;
    let n_each = 10000;

    let begin = Instant::now();
    for _i in 0..n_loop{
        for _j in 0..n_each{
            f_for(&a,&b,&mut c);
        }
    }
    let end = Instant::now();
    println!("for:   {:?}", (end - begin)/n_loop/n_each);
    println!("{:.3}", c[N-3]);

    let begin = Instant::now();
    for _i in 0..n_loop{
        for _j in 0..n_each{
            f_rayon(&a,&b,&mut c);
        }
    }
    let end = Instant::now();
    println!("rayon: {:?}", (end - begin)/n_loop/n_each);
    println!("{:.3}", c[N-3]);


}
