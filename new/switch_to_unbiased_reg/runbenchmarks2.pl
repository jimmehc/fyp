#!/usr/bin/perl

use Switch;
my @algorithms = ("SPL","FP", "AFP", "MP", "AMP", "QFP", "MPQ");
my @options;

my $delay;
if(@ARGV >= 2)
{
	if($ARGV[0] eq "l")
	{
		@options = ("EF", "E", "SF", "S");
	}
	else
	{
		@options = ("NNPNNN", "NNPNN", "NNPN", "NN", "NF","N");
	}
	$delay = $ARGV[1];
}
else
{
	$delay = 0;
	@options = ("NNPNNN", "NNPNN");#, "NNPN", "NN", "NF","N");
}

my %arr;

$arr{"SPL"}{"NNPNNN"} = 51066018560;
$arr{"SPL"}{"NNPNN"} = 51140560736; 


foreach $option (@options)
{
	switch($option)
	{
		case "NNPNNN" { print "99.999% Dominance"; }
		case "NNPNN" { print "99.99% Dominance"; }
		case "NNPN" { print "99.9% Dominance"; }
		case "NN" { print "99% Dominance"; }
		case "NF" { print "95% Dominance"; }
		case "N" { print "90% Dominance"; }
		case "EF" { print "85% Dominance"; }
		case "E" { print "80% Dominance"; }
		case "SF" { print "75% Dominance"; }
		case "S" { print "70% Dominance"; }
	}

	print "\n";
	foreach $algorithm (@algorithms)
	{
		if($algorithm ne "SPL") 
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
			case "QFP" { print "Queue of Function Pointers"; }
			case "MPQ" { print "Queue of Messages"; }
		}
		print "\n";
		print `make DELAY=$delay ALG=$algorithm DOM=$option`;
	
		$output = `./asymmetric`;
		if($output =~ m/Tipping point/)
		{
			$arr{$algorithm}{$option} = 0;
		}
		else
		{
			$output =~ m/time: (.*)/;
			$arr{$algorithm}{$option} = $1;
		}
		print $arr{$algorithm}{$option};
		print "\n";
	}
	}
	print "\n";

}
$machinename = `hostname -s`;
$num = `ls -l results|wc -l` + 1;

chomp($machinename);

$filename = $machinename."_delay".$delay."_".$ARGV[0]."_".$num;

print $filename;

`mkdir results`;
`mkdir graphs`;

open FILE, ">","results/$filename.gr" or die "WAT";

print FILE "=cluster;Spinlock(baseline);One Function Pointer;Asynchronous FP;Message Passing;Asynchronous Message Passing;Function Pointer Queue;Message Passing Queue;\n=table\nyformat=%gx\n=norotate\nylabel=Speedup\nxlabel=Dominance Percentage\n\n"; 


print FILE "#";
foreach $algorithm (@algorithms)
{
	print FILE $algorithm;
	print FILE " ";
}

print FILE "\n";

foreach $option (@options)
{
	switch($option)
	{
		case "NNPNNN" { print FILE "99.999"; }
		case "NNPNN" { print FILE "99.99"; }
		case "NNPN" { print FILE "99.9"; }
		case "NN" { print FILE "99"; }
		case "NF" { print FILE "95"; }
		case "N" { print FILE "90"; }
		case "EF" { print FILE "85"; }
		case "E" { print FILE "80"; }
		case "SF" { print FILE "75"; }
		case "S" { print FILE "70"; }
	}
	print FILE " ";
	foreach $algorithm (@algorithms)
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

open FILE, ">","results/$filename.raw" or die "WAT";

foreach $algorithm (@algorithms)
{
	print FILE $algorithm;
	print FILE " ";
	foreach $option (@options)
	{
		print FILE $arr{$algorithm}{$option};
		print FILE " ";
	}	
	print FILE "\n";
}
close FILE;

print `perl ../../bargraph.pl -png results/$filename.gr > graphs/$filename.png`;
