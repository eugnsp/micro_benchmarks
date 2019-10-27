#!/usr/bin/perl

my %data;
while (<STDIN>)
{
	my ($name, $bps, $fact, $size) = m{(.*?)/.*items_per_second=([0-9.]+)([KMG]?)[^\s]+\s(\d+)};
	next unless defined $name;

	$bps /= 1E6 if $fact eq 'K';
	$bps /= 1E3 if $fact eq 'M';
	$data{$name} .= "$size\t$bps\n";
}

foreach my $fname (keys %data)
{
	open(my $f, '>', "$fname.dat");
	print $f $data{$fname};
	close $f;
}
