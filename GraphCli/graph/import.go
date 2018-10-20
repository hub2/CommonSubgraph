package graph

import (
	"bufio"
	"fmt"
	"io"
	"strconv"
	"strings"
)

const (
	valuesDelim = ","
)

func Import(r io.Reader) (*Builder, error) {
	rd := bufio.NewReader(r)
	line, err := rd.ReadBytes('\n')
	if err != nil {
		return nil, fmt.Errorf("could not get matrix size: %v", err)
	}

	graphSize, err := strconv.Atoi(string(line[:len(line)-1]))
	if err != nil {
		return nil, fmt.Errorf("could not get graph size: %v", err)
	}

	builder, err := New(graphSize)
	if err != nil {
		return nil, fmt.Errorf("could not create graph: %v", err)
	}

	for i := 0; i < graphSize; i++ {
		line, err := rd.ReadBytes('\n')
		if err != nil {
			return nil, fmt.Errorf("could not get matrix line %d : %v", i, err)
		}

		values := strings.Split(string(line[:len(line)-1]), valuesDelim)
		if len(values) != graphSize {
			return nil, fmt.Errorf("bad number of values for vertex: %d, wanted: %d, got %d", i, graphSize, len(values))
		}
		for j := 0; j < graphSize; j++ {
			valInt, err := strconv.Atoi(values[j])
			if err != nil {
				return nil, fmt.Errorf("bad value at cell %d for vertex %d", j, i)
			}
			if valInt == 1 {
				builder.AddEdge(i, j)
			}
		}
	}

	return builder, nil
}
