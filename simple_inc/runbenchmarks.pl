#!/usr/bin/perl

use Switch;

my @algorithms = ("spinlock", "pthread_lock", "control", "asymmetric", "asymmetric_var", "experiment", "experiment2", "experiment3", "experiment4", "queues", "message_passing");
my @algorithms = ("experiment2", "experiment4", "queues", "message_passing");
#my @options = ("nnpnnn", "nnpnn", "nnpn", "nn", "n");
my @options = ("n");

foreach $option (@options)
{
	switch($option)
	{
		case "nnpnnn" { print "99.999% Dominance"; }
		case "nnpnn" { print "99.99% Dominance"; }
		case "nnpn" { print "99.9% Dominance"; }
		case "nn" { print "99% Dominance"; }
		case "n" { print "90% Dominance"; }
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
		`make -C$algorithm $option`;
		print `./$algorithm/asymmetric`;
	}
	print "\n";
}
