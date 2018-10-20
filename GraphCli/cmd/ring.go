package cmd

import (
	"log"

	"github.com/TheMacies/CommonSubgraph/GraphCli/graph"
	"github.com/spf13/cobra"
)

func init() {
	createCmd.AddCommand(ringCmd)
}

var ringCmd = &cobra.Command{
	Use:   "ring",
	Short: "Create ring graph",
	Run: func(cmd *cobra.Command, args []string) {
		if vertices < 3 {
			log.Fatalf("Ring must have at least 3 vertices")
		}

		g, err := graph.New(vertices)
		if err != nil {
			log.Fatalf("Error creating graph: %v", err)
		}

		for i := 0; i < vertices; i++ {
			nextEdge := i + 1
			if i == vertices-1 {
				nextEdge = 0
			}
			g.AddEdge(i, nextEdge)
		}
		exportGraph(g)
	},
}
