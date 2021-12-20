use std::io::{
	self,
	prelude::*,
	BufReader,
};
use std::fs::File;

#[derive(Copy, Clone, Default)]
struct Cell {
	marked: bool,
	number: u32,
}

type Board = [[Cell; 5]; 5];

fn read_draws(reader: &mut BufReader<File>, line: &mut String) -> io::Result<Vec<u32>> {
	reader.read_line(line)?;
	let draws: Vec<u32> = line
		.trim_end()
		.split(',')
		.map(|x| x.parse::<u32>().unwrap())
		.collect();
	line.clear();

	Ok(draws)
}

fn read_boards(reader: &mut BufReader<File>, line: &mut String) -> io::Result<Vec<Board>> {	
	let mut boards: Vec<Board> = vec![];
	loop {
		// if x == 0, then EOF is reached
		let x = reader.read_line(line)?;
		line.clear();
		if x == 0 {
			break;
		}

		let mut board: Board = Default::default();
		for i in 0..5 {
			reader.read_line(line)?;
			for (j, num) in line
				.trim_end()
				.split(' ')
				.filter_map(|x| x.parse::<u32>().ok())
				.enumerate()
			{
				board[i][j] = Cell {
					marked: false,
					number: num,						
				};
			}
			line.clear();
		}
		boards.push(board);
	};

	Ok(boards)
}

fn mark_number(board: &mut Board, number: u32) {
	for x in board {
		for cell in x {
			if cell.number == number {
				cell.marked = true;
			}
		}
	}
}

fn is_bingo(board: &Board) -> bool {
	//check horizontal
	let a = board.iter()
		.any(|&x| x.iter().all(|&y| y.marked));
	let b = (0..board.len())
		.any(|j| (0..board[0].len()).all(|i| board[i][j].marked));

	a || b									   
}

fn sum_of_unmarked(board: &Board) -> u32 {
	board.iter()
		.flatten()
		.filter(|x| !x.marked)
		.fold(0, |acc, x| acc + x.number)
}

fn part1(reader: &mut BufReader<File>) -> io::Result<()> {
	let mut line = String::with_capacity(100);

	let draws: Vec<u32> = read_draws(reader, &mut line)?;
	let mut boards: Vec<Board> = read_boards(reader, &mut line)?;

	'outer: for num in draws {
		for board in &mut boards {
			mark_number(board, num);
			if is_bingo(board) {
				let sum = sum_of_unmarked(board);
				println!("Sum of unmarked numbers: {}", sum);
				println!("Number just called: {}", num);
				println!("Result: {}", sum*num);
				break 'outer;
			}
		}
	}

	Ok(())
}

fn part2(reader: &mut BufReader<File>) -> io::Result<()> {
	let mut line = String::with_capacity(100);

	let draws: Vec<u32> = read_draws(reader, &mut line)?;
	let mut boards: Vec<Board> = read_boards(reader, &mut line)?;
	let mut bingoed = vec![false; boards.len()];
	let mut not_bingoed_count = boards.len();

	let mut last_num: u32 = 0;
	let mut last_sum: u32 = 0;
	'outer: for num in draws {
		for (i, board) in boards.iter_mut().enumerate() {
			if bingoed[i] {
				continue;
			}
			mark_number(board, num);
			if is_bingo(board) {
				bingoed[i] = true;
				not_bingoed_count -= 1;
				last_num = num;
				last_sum = sum_of_unmarked(board);
			}

			if not_bingoed_count == 0 {
				break 'outer;
			}
		}
	}
	
	println!("Sum of unmarked numbers: {}", last_sum);
	println!("Number just called: {}", last_num);
	println!("Result: {}", last_num * last_sum);

	Ok(())	
}

fn main() -> io::Result<()> {
	let f = File::open("input.txt")?;
	// let f = File::open("input.txt")?;
	let mut reader = BufReader::new(f);

	//part1(&mut reader)
	part2(&mut reader)
}
