/*
 * Copyright (C) 2009-2012 the libgit2 contributors
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */
#ifndef INCLUDE_git_diff_tree_h__
#define INCLUDE_git_diff_tree_h__

#include "diff.h"
#include "index.h"

/**
 * @file git2/diff_tree.h
 * @brief Git tree differencing routines.
 *
 * Three-way (ancestor/ours/theirs) tree differencing and arbitrary n-way
 * tree differencing.  When you are done with a tree diff list object,
 * it must be freed.
 *
 * @ingroup Git
 * @{
 */
GIT_BEGIN_DECL

/**
 * Flags for tree_many diff options.  A combination of these flags can be
 * passed in via the `flags` value in the `git_diff_tree_many_options`.
 */
typedef enum {
	/** Return unmodified entries */
	GIT_DIFF_TREE_RETURN_UNMODIFIED = (1 << 0),
} git_diff_tree_option_t;

typedef enum {
	GIT_DIFF_TREE_CONFLICT_NONE = 0,
	GIT_DIFF_TREE_CONFLICT_BOTH_MODIFIED = (1 << 0),
	GIT_DIFF_TREE_CONFLICT_BOTH_ADDED = (1 << 1),
	GIT_DIFF_TREE_CONFLICT_BOTH_DELETED = (1 << 2),
	GIT_DIFF_TREE_CONFLICT_MODIFY_DELETE = (1 << 3),
} git_diff_tree_conflict_t;

typedef enum {
	GIT_DIFF_TREE_DF_NONE = 0,
	GIT_DIFF_TREE_DF_DIRECTORY_FILE = (1 << 0),
	GIT_DIFF_TREE_DF_CHILD = (1 << 1),
} git_diff_tree_df_conflict_t;

/**
 * The git_diff_tree_list list object that contains all individual
 * object deltas.
 */
typedef struct git_diff_tree_list git_diff_tree_list;

/**
 * Description of changes to one file in a tree.
 */
typedef struct {
    git_diff_file file;
    git_delta_t status;
} git_diff_tree_entry;

/**
 * Description of changes to one file across three trees.
 */
typedef struct {
    git_diff_tree_entry ancestor;
    git_diff_tree_entry ours;
    git_diff_tree_entry theirs;
	git_diff_tree_conflict_t conflict;
	git_diff_tree_df_conflict_t df_conflict;
} git_diff_tree_delta;

/** Callback for the tree difference function. */
typedef int (*git_diff_tree_many_cb)(const git_index_entry **tree_items, void *payload);

/** Callback for the 3-way tree difference function */
typedef int (*git_diff_tree_delta_cb)(const git_diff_tree_delta *delta, void *payload);

/** @name Tree Diff Functions
 *
 * Functions that operate on an arbitrary number of trees.
 */
/**@{*/

/**
 * Iterate many trees and issue a callback for each entry that differs
 * in one (or more) of the trees.
 *
 * @param repo The repository containing the trees.
 * @param trees An array of git_tree objects to diff.
 * @param trees_length The number of trees to difference
 * @param flags A combination of git_diff_tree_option_t values above (default 0)
 * @param callback Callback function to make with each different tree entry.
 * @param payload Reference pointer that will be passed to your callback.
 * @return 0 on success, GIT_EUSER on non-zero callback, or error code
 */
GIT_EXTERN(int) git_diff_tree_many(
	git_repository *repo,
	git_tree **trees,
	size_t trees_length,
	uint32_t flags,
	git_diff_tree_many_cb callback,
	void *payload);

/**@}*/

/** @name Three-way Tree Diff Functions
 *
 * Functions that operate on three trees, a common ancestor, and two
 * child trees ("ours" and "theirs").
 *
 * @param out Pointer to a git_diff_tree_list that will be allocated.
 * @param repo The repository containing the trees.
 * @param ancestor_tree The git_tree object representing the common ancestor.
 * @param our_tree The git_tree object representing the "ours" side.
 * @param their_tree The git_tree object representing the "theirs" side.
 * @param flags A combination of git_diff_tree_option_t values above (default 0)
 * @return 0 on success, or error code
 */
/**@{*/

GIT_EXTERN(int) git_diff_tree(
	git_diff_tree_list **out,
	git_repository *repo,
	git_tree *ancestor_tree,
	git_tree *our_tree,
	git_tree *their_tree,
	uint32_t flags);

/**
 * Loop over the differences between the trees and issue a callback for each
 * one.
 *
 * If the callback returns a non-zero value, this will stop looping.
 *
 * @param diff Diff list to iterate over.
 * @param callback Callback function to make with each different tree entry.
 * @param payload Reference pointer that will be passed to your callback.
 * @return 0 on success, GIT_EUSER on non-zero callback, or error code
 */
GIT_EXTERN(int) git_diff_tree_foreach(
	git_diff_tree_list *diff,
	git_diff_tree_delta_cb callback,
	void *payload);

/**
 * Deallocate a diff_tree list.
 */
GIT_EXTERN(void) git_diff_tree_list_free(git_diff_tree_list *diff_tree);

/**@}*/

GIT_END_DECL

/** @} */

#endif
