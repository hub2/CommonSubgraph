package cmd

import (
	"log"

	"github.com/TheMacies/CommonSubgraph/GraphCli/graph"
	"github.com/spf13/cobra"
)

func init() {
	createCmd.AddCommand(lineCmd)
}

var lineCmd = &cobra.Command{
	Use:   "line",
	Short: "Create line graph",
	Run: func(cmd *cobra.Command, args []string) {
		g, err := graph.New(vertices)
		if err != nil {
			log.Fatalf("Error creating graph: %v", err)
		}

		for i := 0; i < vertices-1; i++ {
			nextEdge := i + 1
			g.AddEdge(i, nextEdge)
		}
		exportGraph(g)
	},
}
