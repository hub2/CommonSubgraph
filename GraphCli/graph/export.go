package graph

import (
	"errors"
	"fmt"
	"io"
	"strconv"
)

func Export(g *Builder, out io.Writer) error {
	if g == nil {
		return errors.New("cannot export nil graph")
	}

	_, err := out.Write([]byte(fmt.Sprintf("%d\n", len(g.adjMatrix))))
	if err != nil {
		return fmt.Errorf("could not write to output: %s", err.Error())
	}

	for i := range g.adjMatrix {
		row := g.adjMatrix[i]
		for j := range row {
			cell := strconv.Itoa(row[j])
			if j != len(row)-1 {
				cell += valuesDelim
			}
			_, err := out.Write([]byte(cell))
			if err != nil {
				return fmt.Errorf("could not write to output: %s", err.Error())
			}
		}

		_, err := out.Write([]byte("\n"))
		if err != nil {
			return fmt.Errorf("could not write to output: %s", err.Error())
		}
	}
	return nil
}
