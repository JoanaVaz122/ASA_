use std::cmp::max;
use std::io;

fn max_cut_value(x: usize, y: usize, parts: &Vec<Vec<usize>>) -> usize {
    let n = parts.len();

    let mut dp = vec![vec![0; y + 1]; x + 1];

    for i in 1..=x {
        for j in 1..=y {
            dp[i][j] = dp[i][j - 1];

            for k in 0..n {
                let ai = parts[k][0];
                let bi = parts[k][1];
                let pi = parts[k][2];

                if (i >= ai && j >= bi) || (i >= bi && j >= ai) {
                    if x % bi == 0 && y % ai == 0 {
                        dp[i][j] = max(dp[i][j], max(dp[i][j - ai] + pi, dp[i - bi][j] + pi));
                    } else if x % ai == 0 && y % bi == 0 {
                        dp[i][j] = max(dp[i][j], max(dp[i][j - bi] + pi, dp[i - ai][j] + pi));
                    }
                }
            }
        }
    }

    dp[x][y]
}

fn main() {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let input: Vec<usize> = input_line.split_whitespace().map(|x| x.trim().parse().unwrap()).collect();

    let x = input[0];
    let y = input[1];
    let n = input[2];

    if x == 0 || y == 0 || n == 0 {
        println!("0");
        return;
    }

    let mut parts_type = Vec::with_capacity(n);

    for _ in 0..n {
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        let part: Vec<usize> = input_line.split_whitespace().map(|x| x.trim().parse().unwrap()).collect();
        parts_type.push(part);
    }

    let result = max_cut_value(x, y, &parts_type);
    println!("{}", result);
}
