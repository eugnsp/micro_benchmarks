#!/usr/bin/perl

my %data;
while (<STDIN>)
{
	my ($name, $ps, $fact, $size) = m{(.*?)/.*per_second=([0-9.]+)([kMG]?)[^\s]+\s(\d+)};
	next unless defined $name;

	$ps /= 1E6 if $fact eq 'k';
	$ps /= 1E3 if $fact eq 'M';
	$data{$name} .= "$size\t$ps\n";
}

foreach my $fname (keys %data)
{
	open(my $f, '>', "$fname.dat");
	print $f $data{$fname};
	close $f;
}
