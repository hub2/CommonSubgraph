package cmd

import (
	"log"
	"os"

	"github.com/TheMacies/CommonSubgraph/GraphCli/graph"
	"github.com/spf13/cobra"
)

var (
	vertices int
	outPath  string
)

func init() {
	rootCmd.AddCommand(createCmd)
	createCmd.PersistentFlags().StringVarP(&outPath, "output", "o", "", "path to file where graph will be stored")
	createCmd.PersistentFlags().IntVarP(&vertices, "vertices", "v", 0, "number of vertices")
	createCmd.MarkPersistentFlagRequired("vertices")
}

var createCmd = &cobra.Command{
	Use:   "create",
	Short: "Create new graph",
	Run: func(cmd *cobra.Command, args []string) {
		cmd.Usage()
	},
}

func exportGraph(g *graph.Builder) {
	output := os.Stdout
	if outPath != "" {
		file, err := os.Create(outPath)
		if err != nil {
			log.Fatalf("Could not create file: %v", err)
		}
		defer file.Close()
		output = file
	}
	if err := graph.Export(g, output); err != nil {
		log.Fatalf("Could not export graph: %v", err)
	}
}
