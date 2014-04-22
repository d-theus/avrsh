DIAGS=package

all:$(DIAGS:=.pdf)

%.pdf:%.dot
	dot -Tpdf -o $@ $<

