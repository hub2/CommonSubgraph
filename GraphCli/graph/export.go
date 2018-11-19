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
	for i := range g.AdjMatrix {
		row := g.AdjMatrix[i]
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
