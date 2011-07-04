#!/usr/bin/perl

use Switch;
use Getopt::Std;

#filename,delay,long,execute,process,rawout,graphout
&getopts("f:d:lxprgi:b:");

#my @all_algorithms = ("SPL", "VAS", "VASVAR", "FP", "AFP", "MP", "AMP", "ISPL", "ISPLMP", "QFP", "MPQ", "FPR", "AFPR", "MPR", "AMPR","ISPLR", "ISPLMPR", "QFPR", "MPQR");
#my @all_algorithms = ("SPL", "VAS", "VASVAR", "FP", "AFP", "MP", "AMP", "QFP", "MPQ", "FPR", "AFPR", "MPR", "AMPR","ISPLR", "ISPLMPR", "QFPR", "MPQR");
my @all_algorithms = ("SPL", "VAS", "FP", "AFP", "MP", "AMP", "ISPL", "ISPLMP", "FPQ", "MPQ");
my @algorithms_to_run = ("SPL", "VASVAR", "FP", "AFP", "MP", "AMP", "ISPL", "ISPLMP", "FPQ", "MPQ");
#my @algorithms_to_run = ("SPL");
my @options;
my %arr;

my $delay;
if($opt_l)
{
		@options = ("EF", "E", "SF", "S");
}
else
{
	if($opt_b eq "multiple"){
		@options = ("100000", "10000", "1000", "100", "50", "25", "10", "9", "8", "7", "6", "5");
	}
	else
	{
		@options = ("NNPNNN", "NNPNN", "NNPN", "NN", "NE", "NS", "NSI", "NF", "NFO", "NT", "NTW", "NO", "N");
	}
}

if($opt_d)
{
	$delay = $opt_d;
}
else
{
	$delay = 0;
}

$machinename = `hostname -s`;
$num = `ls -l results|wc -l` + 1;
chomp($machinename);

$filename = $opt_b."_".$machinename."_delay".$delay."_".$num;

print $filename;
print "\n";

if($opt_x)
{
	&run_tests;
}
else
{
	if($opt_p)
	{
		&process_raw_data;
	}
	else
	{
		die "no data\n";
	}
}

if($opt_r)
{
	&raw_output;
}

if($opt_g)
{
	&output_graph_file;
	&make_graph;
}


sub run_tests
{
	foreach $option (@options)
	{
		switch($option)
		{
			case "NNPNNN" { print "99.999% Dominance"; }
			case "NNPNN" { print "99.99% Dominance"; }
			case "NNPN" { print "99.9% Dominance"; }
			case "NN" { print "99% Dominance"; }
			case "NE" { print "98% Dominance"; }
			case "NS" { print "97% Dominance"; }
			case "NSI" { print "96% Dominance"; }
			case "NF" { print "95% Dominance"; }
			case "NFO" { print "94% Dominance"; }
			case "NT" { print "93% Dominance"; }
			case "NTW" { print "92% Dominance"; }
			case "NO" { print "91% Dominance"; }
			case "N" { print "90% Dominance"; }
			case "EF" { print "85% Dominance"; }
			case "E" { print "80% Dominance"; }
			case "SF" { print "75% Dominance"; }
			case "S" { print "70% Dominance"; }
		}

		print "\n";
		foreach $algorithm (@algorithms_to_run)
		{
			switch($algorithm)
			{
				case "SPL" { print "Spinlock"; }
				case "PTM" { print "Pthread Mutex"; }
				case "CTRL" {print "Control"; }
				case "VAS" { print "Asymmetric (Vasuvedan)"; }
				case "VASVAR" { print "Asymmetric Variation"; }
				case "FP" { print "Function Pointer Passing"; }
				case "AFP" { print "Asynchronous Function Pointer Passing"; }
				case "MP" { print "Message Passing"; }
				case "AMP" { print "Asynchronous Message Passing"; }
				case "ISPL" { print "Integrated Spinlock"; }
				case "ISPLMP" { print "Integrated Message Passing Spinlock"; }
				case "QFP" { print "Queue of Function Pointers"; }
				case "MPQ" { print "Queue of Messages"; }
				case "FPR" { print "Function Pointer Passing (Register)"; }
				case "AFPR" { print "Asynchronous Function Pointer Passing (Register)"; }
				case "MPR" { print "Message Passing (Register)"; }
				case "AMPR" { print "Asynchronous Message Passing (Register)"; }
				case "ISPLR" { print "Integrated Spinlock (Register)"; }
				case "ISPLMPR" { print "Integrated Message Passing Spinlock (Register)"; }
				case "QFPR" { print "Queue of Function Pointers (Register)"; }
				case "MPQR" { print "Queue of Messages (Register)"; }

			
			}
			print "\n";
			
			if($opt_b eq "multiple")
			{
				print `g++ -o $opt_b $opt_b.cpp -D$algorithm -DLOOP -DMULTIPLE -O3 -DNDF=$option -lpthread`;
			}
			else
			{
				print `g++ -o $opt_b $opt_b.cpp -D$algorithm -DLOOP -O3 -D$option -lpthread`;
			}
			my @res;
			for($i = 0; $i < $opt_i; $i++)
			{
				$output = `./$opt_b`;
				$output =~ m/time: (.*)/;
				$res[$i] = $1;
				print $output;
			}

			@res = sort {$a <=> $b} @res;
			$mid = $opt_i/2;

			$arr{$algorithm}{$option} = $res[$mid];
	
			print $arr{$algorithm}{$option};
			print "\n";
		}
		print "\n";

	}
}

sub process_raw_data
{
	open DATA, "<",$opt_f or die "WAT";

	my @lines = <DATA>;

	close DATA;

	foreach $line (@lines)
	{	
		@alginfo = split(/ /, $line);
		$algorithm = $alginfo[0];
		for($i = 1; $i < @alginfo; $i = $i + 2)
		{
			$arr{$algorithm}{$alginfo[$i]} = $alginfo[$i+1];
		}
	}
}



sub output_graph_file
{


	open FILE, ">","results/$filename.gr" or die "WAT";

	print FILE "=cluster;";
	
	foreach $algorithm (@all_algorithms)
	{
		switch($algorithm)
		{
			case "SPL" { print FILE "Spinlock;"; }
			case "PTM" { print FILE "Pthread Mutex;"; }
			case "CTRL" {print FILE "Control;"; }
			case "VAS" { print FILE "Asymmetric (Vasuvedan);"; }
			case "VASVAR" { print FILE "Asymmetric Variation;"; }
			case "FP" { print FILE "Function Pointer Passing;"; }
			case "AFP" { print FILE "Asynchronous Function Pointer Passing;"; }
			case "MP" { print FILE "Message Passing;"; }
			case "AMP" { print FILE "Asynchronous Message Passing;"; }
			case "ISPL" { print FILE "Integrated Spinlock;"; }
			case "ISPLMP" { print FILE "Integrated Message Passing Spinlock;"; }
			case "FPQ" { print FILE "Queue of Function Pointers;"; }
			case "MPQ" { print FILE "Queue of Messages;"; }
			case "FPR" { print FILE "Function Pointer Passing (Register);"; }
			case "AFPR" { print FILE "Asynchronous Function Pointer Passing (Register);"; }
			case "MPR" { print FILE "Message Passing (Register);"; }
			case "AMPR" { print FILE "Asynchronous Message Passing (Register);"; }
			case "ISPLR" { print FILE "Integrated Spinlock (Register);"; }
			case "ISPLMPR" { print FILE "Integrated Message Passing Spinlock (Register);"; }
			case "QFPR" { print FILE "Queue of Function Pointers (Register);"; }
			case "MPQR" { print FILE "Queue of Messages (Register)"; }
		}
	}

	print FILE "\n=table\nyformat=%gx\n=norotate\nylabel=Speedup\nxlabel=Non Dom Access Period\n"; 


	print FILE "#";
	foreach $algorithm (@all_algorithms)
	{
		print FILE $algorithm;
		print FILE " ";
	}

	print FILE "\n";

	foreach $option (@options)
	{
		print FILE "$option ";
		foreach $algorithm (@all_algorithms)
		{
#		if($algorithm ne "control")
#		{
				if($arr{$algorithm}{$option} != 0)
				{
					print FILE $arr{"SPL"}{$option}/$arr{$algorithm}{$option};
				}
				else
				{
					print FILE 0;
				}
				print FILE " ";
#		}
		}
		print FILE "\n";
	}
	close FILE;
}

sub raw_output
{
	open FILE, ">","results/$filename.raw" or die "WAT";

	foreach $algorithm (@algorithms_to_run)
	{
		print FILE $algorithm;
		print FILE " ";
		foreach $option (@options)
		{
			print FILE $option;
			print FILE " ";
			print FILE $arr{$algorithm}{$option};
			print FILE " ";
		}	
		print FILE "\n";
	}
	close FILE;
}

sub make_graph
{
	print `perl ../../bargraph.pl -png results/$filename.gr > graphs/$filename.png`;
	print `scp graphs/$filename.png 134.226.38.27:~/results/.`;
}



