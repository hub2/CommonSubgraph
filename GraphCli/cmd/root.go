package cmd

import (
	"fmt"
	"os"

	"github.com/spf13/cobra"
)

func init() {
}

var rootCmd = &cobra.Command{
	Use:   "graph",
	Short: "Graphs manager",
	Run: func(cmd *cobra.Command, args []string) {
		cmd.Usage()
	},
}

//Execute starts inits CLI
func Execute() {
	if err := rootCmd.Execute(); err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}
