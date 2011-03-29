#!/usr/bin/perl

use Switch;

<<<<<<< HEAD
my @algorithms = ("spinlock", "control", "asymmetric", "asymmetric_var", "experiment", "experiment2", "experiment3", "experiment4", "queues", "message_passing");
my @options = ("nnpnnn", "nnpnn", "nnpn", "nn", "nf","n");
#, "ef", "e", "sf", "s");

my $delay;
if(@ARGV >= 1)
{
	$delay = $ARGV[0];
}
else
{
	$delay = 0;
}

my %arr;

foreach $option (@options)
{
	switch($option)
	{
		case "nnpnnn" { print "99.999% Dominance"; }
		case "nnpnn" { print "99.99% Dominance"; }
		case "nnpn" { print "99.9% Dominance"; }
		case "nn" { print "99% Dominance"; }
		case "nf" { print "95% Dominance"; }
		case "n" { print "90% Dominance"; }
		case "ef" { print "85% Dominance"; }
		case "e" { print "80% Dominance"; }
		case "sf" { print "75% Dominance"; }
		case "s" { print "70% Dominance"; }
	}

	print "\n";
	foreach $algorithm (@algorithms)
	{
		switch($algorithm)
		{
			case "spinlock" { print "Spinlock"; }
			case "pthread_lock" { print "Pthread Mutex"; }
			case "control" {print "Control"; }
			case "asymmetric" { print "Asymmetric (Vasuvedan)"; }
			case "asymmetric_var" { print "Asymmetric Variation"; }
			case "experiment" { print "Function Pointer Passing"; }
			case "experiment2" { print "Asynchronous Function Pointer Passing"; }
			case "experiment3" { print "Message Passing"; }
			case "experiment4" { print "Integrated Spinlock"; }
			case "queues" { print "Queue of Function Pointers"; }
			case "message_passing" { print "Queue of Messages"; }
		}
		print "\n";
		`make DELAY=$delay -C$algorithm $option`;
		if(`./$algorithm/asymmetric` =~ m/time: (.*)/)
		{
			$arr{$algorithm}{$option} = $1;
		}
		else
		{
			$arr{$algorithm}{$option} = 0;
		}
		print $arr{$algorithm}{$option};
		print "\n";
	}
	print "\n";

}
foreach $algorithm (@algorithms)
{
	print $algorithm;
	print " ";
	foreach $option (@options)
	{
		print $arr{$algorithm}{$option};
		print " ";
	}
	print "\n";
}

