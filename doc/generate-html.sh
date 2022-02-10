#!/bin/sh

mkdir -p html

rm -f html/*

asciidoctor small_flat_map.asciidoc -o html/small_flat_map.html

asciidoctor small_flat_multimap.asciidoc -o html/small_flat_multimap.html

asciidoctor small_flat_set.asciidoc -o html/small_flat_set.html

asciidoctor small_flat_multiset.asciidoc -o html/small_flat_multiset.html

asciidoctor small_unordered_flat_map.asciidoc -o html/small_unordered_flat_map.html

asciidoctor small_unordered_flat_multimap.asciidoc -o html/small_unordered_flat_multimap.html

asciidoctor small_unordered_flat_set.asciidoc -o html/small_unordered_flat_set.html

asciidoctor small_unordered_flat_multiset.asciidoc -o html/small_unordered_flat_multiset.html

asciidoctor small_vector.asciidoc -o html/small_vector.html
